#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <algorithm>

#include "mesh_connector.h"

using std::pair;

cd_link_t CDMeshConnector::get_new_map_id() {
	return _fresh_map_id++;
}

CDMeshConnector::CDMeshConnector() {
	printf("adding dummy node and automation...\n");

	char* temp_node_berta_name = (char*) malloc(5);
	strncpy(temp_node_berta_name, "berta", 5);

	cd_s_node* temp_node_berta = (cd_s_node*) malloc(sizeof(cd_s_node));
	temp_node_berta->name = temp_node_berta_name;
	temp_node_berta->name_len = 5;
	temp_node_berta->light_on = false;
	temp_node_berta->provisioned = false;
	cd_mac_addr_t temp_node_berta_address = { 0x00, 0xff, 0x21, 0x69, 0xf2, 0x31 };
	strncpy((char*)temp_node_berta->address, (char*)&temp_node_berta_address, 6);

	_nodes.push_back(temp_node_berta);
	set_link(temp_node_berta, temp_node_berta, CD_AUTOMATION_TYPE_TOGGLE);
	return;
}

CDMeshConnector::~CDMeshConnector() {
	map<cd_link_t, cd_s_automation*> links = get_links();
	vector<cd_s_node*> nodes = get_nodes();

	// free all automation structs
	for (pair<cd_link_t, cd_s_automation*> link : links)
		remove_link(link.first);

	// free all node structs
	for (cd_s_node* node : nodes)
		if (node != nullptr) free(node);

	return;
}

void CDMeshConnector::refresh_config_sync() {
	return;
}

void CDMeshConnector::refresh_nodes_sync() {
	return;
}

vector<cd_s_node*> CDMeshConnector::get_nodes() {
	return _nodes;
}

map<cd_link_t, cd_s_automation*> CDMeshConnector::get_links() {
	return _links;
}

vector<cd_s_automation*> CDMeshConnector::get_config() {
	vector<cd_s_automation*> automations;
	map<cd_link_t, cd_s_automation*> links = get_links();
	for (pair<cd_link_t, cd_s_automation*> link : links)
		automations.push_back(link.second);
	return automations;
}

cd_link_t CDMeshConnector::set_link(cd_s_node* button, cd_s_node* light, enum cd_e_automation_type action) {
	cd_s_automation* automation = (cd_s_automation*) malloc(sizeof(cd_s_automation));
	automation->button = button;
	automation->light = light;
	automation->type = action;

	cd_link_t link = get_new_map_id();
	_links[link] = automation;

	printf("new link[%d]: %.*s %s %.*s\n", link, (int) button->name_len, button->name, action == CD_AUTOMATION_TYPE_TOGGLE ? "toggles" : action == CD_AUTOMATION_TYPE_TURN_OFF ? "turns off" : "turns on", (int) light->name_len, light->name);
	return link;
}

void CDMeshConnector::remove_link(cd_link_t link_handle) {
	printf("remove link[%d]\n", link_handle);
	if (_links[link_handle] != nullptr) free(_links[link_handle]);
	_links.erase(link_handle);
	return;
}

cd_s_node* CDMeshConnector::get_node_by_id(cd_mac_addr_t address) {
	cd_s_node* node = std::find_if(_nodes.begin(), _nodes.end(),
		[address] (const cd_s_node* n) {
			return strncmp((char*)n->address, (char*)address, 6);
		})[0];
	return node;
}

void CDMeshConnector::set_node(cd_s_node* node_ptr, bool light_status) {
	node_ptr->light_on = light_status;
	printf("turning %.*s %s\n", (int) node_ptr->name_len, node_ptr->name, node_ptr->light_on ? "on" : "off");
	return;
}

void CDMeshConnector::node_join_network(cd_s_node* node_ptr) {
	node_ptr->provisioned = true;
	printf("join %.*s into network\n", (int) node_ptr->name_len, node_ptr->name);
	return;
}

void CDMeshConnector::node_remove_network(cd_s_node* node_ptr) {
	node_ptr->provisioned = false;
	printf("remove %.*s from network\n", (int) node_ptr->name_len, node_ptr->name);
	return;
}

string cd_node_mac_string(cd_mac_addr_t mac) {
	char* addr = nullptr;
	asprintf(&addr, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	string ret = addr;
	free(addr);
	return ret;
}
