#pragma once

#include <stdint.h>
#include <vector>
#include <map>
#include <string>

typedef uint32_t cd_link_t;
typedef uint8_t cd_mac_addr_t[6];

using std::size_t;
using std::vector;
using std::map;
using std::string;

enum cd_e_automation_type {
	CD_AUTOMATION_TYPE_TOGGLE,
	CD_AUTOMATION_TYPE_TURN_ON,
	CD_AUTOMATION_TYPE_TURN_OFF,
};

typedef struct {
	cd_mac_addr_t address;
	size_t name_len;
	const char* name;
	bool light_on;
	bool provisioned;
} cd_s_node;

typedef struct {
	cd_e_automation_type type;
	cd_s_node* button;
	cd_s_node* light;
} cd_s_automation;

class CDMeshConnector {
private:
	vector<cd_s_node*> _nodes;
	map<cd_link_t, cd_s_automation*> _links;
	cd_link_t _fresh_map_id;
	virtual cd_link_t get_new_map_id();
public:
	CDMeshConnector();
	virtual ~CDMeshConnector();
	virtual void refresh_nodes_sync();
	virtual void refresh_config_sync();
	virtual vector<cd_s_node*> get_nodes();
	virtual map<cd_link_t, cd_s_automation*> get_links();
	virtual vector<cd_s_automation*> get_config();
	virtual cd_link_t set_link(cd_s_node* button, cd_s_node* light, enum cd_e_automation_type action);
	virtual void remove_link(cd_link_t link_handle);
	virtual cd_s_node* get_node_by_id(cd_mac_addr_t address);
	virtual void set_node(cd_s_node* node_ptr, bool light_status);
	virtual void node_join_network(cd_s_node* node_ptr);
	virtual void node_remove_network(cd_s_node* node_ptr);
};

string cd_node_mac_string(cd_mac_addr_t mac);
