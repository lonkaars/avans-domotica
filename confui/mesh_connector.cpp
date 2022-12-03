#include <cstdio>
#include "mesh_connector.h"

CDMeshConnector::CDMeshConnector() {
	return;
}

CDMeshConnector::~CDMeshConnector() {
	return;
}

void CDMeshConnector::refresh_config_sync() {
	return;
}

void CDMeshConnector::refresh_nodes_sync() {
	return;
}

vector<cd_s_node> CDMeshConnector::get_nodes() {
	return {};
}

vector<cd_s_automation> CDMeshConnector::get_config() {
	return {};
}

cd_link_t CDMeshConnector::set_link(cd_mac_addr_t button, cd_mac_addr_t light) {
	(void) button;
	(void) light;
	return 0;
}

void CDMeshConnector::remove_link(cd_link_t link_handle) {
	(void) link_handle;
	return;
}

cd_s_node* CDMeshConnector::get_node_by_id(cd_mac_addr_t address) {
	(void) address;
	return nullptr;
}

void CDMeshConnector::set_node(cd_s_node* node_ptr, bool light_status) {
	(void) node_ptr;
	(void) light_status;
	return;
}

void CDMeshConnector::node_join_network(cd_s_node* node_ptr) {
	(void) node_ptr;
	return;
}

void CDMeshConnector::node_remove_network(cd_s_node* node_ptr) {
	(void) node_ptr;
	return;
}

string cd_node_mac_string(cd_mac_addr_t mac) {
	char* addr = nullptr;
	asprintf(&addr, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	string ret = addr;
	free(addr);
	return ret;
}
