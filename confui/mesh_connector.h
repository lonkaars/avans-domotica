#pragma once

#include <stdint.h>
#include <vector>
#include <map>
#include <string>

using std::size_t;
using std::vector;
using std::map;
using std::string;
using std::array;

typedef uint32_t cd_uid_t;
typedef uint32_t cd_link_t;
typedef uint8_t cd_mac_addr_t[6];

enum cd_e_automation_type {
	CD_AUTOMATION_TYPE_TOGGLE,
	CD_AUTOMATION_TYPE_TURN_ON,
	CD_AUTOMATION_TYPE_TURN_OFF,
};

typedef struct {
	cd_uid_t id;
	cd_mac_addr_t address;
	size_t name_len;
	const char* name;
	bool light_on;
	bool provisioned;
} cd_s_node;

typedef struct {
	cd_link_t id;
	cd_e_automation_type type;
	cd_s_node* button;
	cd_s_node* light;
	bool valid;
} cd_s_automation;

class CDMeshConnector {
private:
	map<cd_link_t, cd_s_automation*> _links;
	map<cd_uid_t, cd_s_node*> _nodes;

	virtual cd_link_t get_new_link_id();
	virtual cd_uid_t get_new_node_id();

	cd_link_t _fresh_link_id = 0;
	cd_uid_t _fresh_node_id = 0;

	virtual cd_uid_t create_node(cd_s_node node);
	virtual void remove_node(cd_uid_t node_handle);

public:
	CDMeshConnector();
	virtual ~CDMeshConnector();

	// (UNUSED/UNIMPLEMENTED) refresh functions
	virtual void refresh_nodes_sync();
	virtual void refresh_config_sync();

	// data fetching functions
	virtual map<cd_link_t, cd_s_automation*> get_links(bool valid = true);
	virtual map<cd_uid_t, cd_s_node*> get_nodes(bool provisioned = false);
	virtual cd_s_automation* get_link(cd_link_t id);
	virtual cd_s_node* get_node(cd_uid_t id);

	// network modification functions
	/** @brief create empty automation */
	virtual cd_link_t create_link();
	/** @brief create valid automation */
	virtual cd_link_t create_link(cd_uid_t button, cd_uid_t light, enum cd_e_automation_type action);
	virtual void update_link(cd_link_t link, cd_s_automation* automation);
	virtual void remove_link(cd_link_t link_handle);

	virtual void update_node(cd_s_node* node_ptr);
	virtual void network_join_node(cd_s_node* node_ptr);
	virtual void network_remove_node(cd_s_node* node_ptr);

	// conversion functions
	static string cd_mac_to_string(cd_mac_addr_t mac);
};

extern CDMeshConnector* g_cd_mesh_connector;

