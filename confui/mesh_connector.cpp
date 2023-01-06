#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <stdio.h>

#include "../shared/pclient.h"
#include "mesh_connector.h"

using std::pair;

void CDMeshConnector::refresh_config_sync() {}
void CDMeshConnector::refresh_nodes_sync() {}

cd_link_t CDMeshConnector::get_new_link_id() { return _fresh_link_id++; }

cd_uid_t CDMeshConnector::get_new_node_id() { return _fresh_node_id++; }

CDMeshConnector::CDMeshConnector() {
	// cd_uid_t berta = create_node({
	// 	.address	 = {0x00, 0xff, 0x21, 0x69, 0xf2, 0x31},
	// 	.name_len	 = 5,
	// 	.name		 = "berta",
	// 	.light_on	 = false,
	// 	.provisioned = false,
	// });

	// cd_uid_t gerrit = create_node({
	// 	.address	 = {0x0e, 0xf9, 0x46, 0x4d, 0xe8, 0x02},
	// 	.name_len	 = 6,
	// 	.name		 = "gerrit",
	// 	.light_on	 = false,
	// 	.provisioned = false,
	// });

	// create_link(berta, berta, CD_AUTOMATION_TYPE_TOGGLE);
	// create_link(berta, berta, CD_AUTOMATION_TYPE_TOGGLE);
	// create_link(gerrit, berta, CD_AUTOMATION_TYPE_TURN_OFF);
	// create_link(gerrit, gerrit, CD_AUTOMATION_TYPE_TURN_ON);
	return;
}

cd_uid_t CDMeshConnector::create_node(cd_s_node node) {
	cd_s_node *_node = (cd_s_node *)malloc(sizeof(cd_s_node));
	// TODO: handle empty structs

	// id
	cd_uid_t id = get_new_node_id();
	_node->id	= id;
	// address
	memcpy(_node->address, node.address, sizeof(cd_mac_addr_t));
	// name len
	_node->name_len = node.name_len;
	// name
	char *name = (char *)malloc(node.name_len);
	memcpy(name, node.name, node.name_len);
	_node->name = name;
	// light on
	_node->light_on = node.light_on;
	// provisioned
	_node->provisioned = node.provisioned;

	printf("(new) node[%d] = %.*s\n", id, (int)node.name_len, node.name);

	_nodes[id] = _node;
	return id;
}

CDMeshConnector::~CDMeshConnector() {
	// free all automation structs
	for (pair<cd_link_t, cd_s_automation *> link : _links) remove_link(link.first);

	// free all node structs
	for (pair<cd_uid_t, cd_s_node *> node : _nodes) remove_node(node.first);

	return;
}

map<cd_uid_t, cd_s_node *> CDMeshConnector::get_nodes(bool provisioned) {
	if (provisioned == false) return _nodes;

	// filter only if provisioned nodes are desired
	map<cd_uid_t, cd_s_node *> nodes;
	for (pair<cd_uid_t, cd_s_node *> node : _nodes) {
		if (node.second->provisioned == false) continue;
		nodes[node.first] = node.second;
	}
	return nodes;
}

map<cd_link_t, cd_s_automation *> CDMeshConnector::get_links(bool valid) {
	if (valid == false) return _links;

	// filter only if valid links are desired
	map<cd_link_t, cd_s_automation *> links;
	for (pair<cd_link_t, cd_s_automation *> link : _links) {
		if (link.second->valid == false) continue;
		links[link.first] = link.second;
	}
	return links;
}

void CDMeshConnector::update_link(cd_s_automation *automation, bool publish) {
	printf("link[%d]", automation->id);
	if (automation->valid) {
		printf(" = %.*s %s %.*s", (int)automation->button->name_len, automation->button->name,
			   automation->type == CD_AUTOMATION_TYPE_TOGGLE	 ? "toggles"
			   : automation->type == CD_AUTOMATION_TYPE_TURN_OFF ? "turns off"
																 : "turns on",
			   (int)automation->light->name_len, automation->light->name);
	} else {
		printf(" (invalid)");
	}
	printf("\n");

	if (!publish) return;
	if (!automation->valid) return;

	cd_s_bin* msg = cd_cmd_gen_post_link_add(automation->button->uuid, automation->light->uuid, automation->type);
	cd_pclient_send(msg);
	free(msg);
}

cd_link_t CDMeshConnector::create_link(cd_uid_t button, cd_uid_t light, cd_e_automation_type type) {
	cd_link_t id = get_new_link_id();

	cd_s_automation *automation = (cd_s_automation *)malloc(sizeof(cd_s_automation));
	automation->id				= id;
	automation->type			= type;
	automation->button			= _nodes[button];
	automation->light			= _nodes[light];
	automation->valid			= true;

	printf("(new) ");
	_links[id] = automation;
	update_link(automation);

	return id;
}

cd_link_t CDMeshConnector::create_link() {
	cd_link_t id = get_new_link_id();

	cd_s_automation *automation = (cd_s_automation *)malloc(sizeof(cd_s_automation));
	automation->id				= id;
	automation->type			= CD_AUTOMATION_TYPE_TOGGLE;
	automation->button			= nullptr;
	automation->light			= nullptr;
	automation->valid			= false;

	printf("(new) ");
	_links[id] = automation;
	update_link(automation);

	return id;
}

void CDMeshConnector::remove_link(cd_link_t link_handle, bool publish) {
	printf("remove link[%d]\n", link_handle);
	if (_links.count(link_handle) == 0) return; // invalid handle
	if (_links[link_handle] == nullptr) return; // already removed link

	cd_s_bin* msg = cd_cmd_gen_post_link_rm(_links[link_handle]->button->uuid, _links[link_handle]->light->uuid);
	cd_pclient_send(msg);
	free(msg);

	free(_links[link_handle]);
	_links[link_handle] = nullptr;
}

void CDMeshConnector::remove_node(cd_uid_t node_handle) {
	printf("remove node[%d]\n", node_handle);
	if (_nodes[node_handle] != nullptr) free(_nodes[node_handle]);
	_nodes[node_handle] = nullptr;
	return;
}

void CDMeshConnector::update_node(cd_s_node *node_ptr, bool publish) {
	printf("turning %.*s %s\n", (int)node_ptr->name_len, node_ptr->name, node_ptr->light_on ? "on" : "off");
	return;
}

void CDMeshConnector::network_join_node(cd_s_node *node_ptr) {
	node_ptr->provisioned = true;
	printf("join %.*s into network\n", (int)node_ptr->name_len, node_ptr->name);
	return;
}

void CDMeshConnector::network_remove_node(cd_s_node *node_ptr) {
	node_ptr->provisioned = false;
	printf("remove %.*s from network\n", (int)node_ptr->name_len, node_ptr->name);
	return;
}

string CDMeshConnector::cd_mac_to_string(cd_mac_addr_t mac) {
	char *addr = nullptr;
	asprintf(&addr, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	string ret = addr;
	free(addr);
	return ret;
}

string CDMeshConnector::cd_uuid_to_string(cd_uuid_t uuid) {
	char *addr = nullptr;
	asprintf(&addr, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x", uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7], uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
	string ret = addr;
	free(addr);
	return ret;
}

cd_s_automation *CDMeshConnector::get_link(cd_link_t id) { return _links[id]; }

cd_s_node *CDMeshConnector::get_node(cd_uid_t id) { return _nodes[id]; }

cd_uid_t CDMeshConnector::get_or_create_node_by_uuid(cd_uuid_t uuid) {
	for (pair<cd_uid_t, cd_s_node *> node : _nodes)
		if (memcmp(node.second->uuid, uuid, sizeof(cd_uuid_t)) == 0) return node.first;
	return create_node({});
}

cd_link_t CDMeshConnector::get_or_create_link_by_uuid(cd_uuid_t button, cd_uuid_t light) {
	for (pair<cd_uid_t, cd_s_automation *> link : _links)
		if (link.second != nullptr && link.second->valid == true &&
			memcmp(link.second->button->uuid, button, sizeof(cd_uuid_t)) == 0 &&
			memcmp(link.second->light->uuid, light, sizeof(cd_uuid_t)) == 0) return link.first;
	return create_link();
}
