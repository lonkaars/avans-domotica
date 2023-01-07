#pragma once

#include <map>
#include <stdint.h>
#include <string>
#include <vector>

#include "../shared/protocol.h"

using std::array;
using std::map;
using std::size_t;
using std::string;
using std::vector;

/** @brief node id type, GUI only */
typedef uint32_t cd_uid_t;
/** @brief link/automation id type */
typedef uint32_t cd_link_t;

typedef cd_e_cmd_link_type cd_e_automation_type;
#define CD_AUTOMATION_TYPE_TOGGLE CD_CMD_LINK_TYPE_TOGGLE
#define CD_AUTOMATION_TYPE_TURN_ON CD_CMD_LINK_TYPE_TURN_ON
#define CD_AUTOMATION_TYPE_TURN_OFF CD_CMD_LINK_TYPE_TURN_OFF

/** @brief GUI node representation */
typedef struct {
	cd_uid_t id;		   /** @brief GUI-specific id (used as handle) */
	cd_mac_addr_t address; /** @brief node bluetooth mac address */
	cd_uuid_t uuid;		   /** @brief node uuid */
	size_t name_len;	   /** @brief name length in bytes */
	char *name;			   /** @brief user-friendly node name */
	bool light_on;		   /** @brief state of light on node */
	bool provisioned;	   /** @brief whether the node is provisioned into the network */
} cd_s_node;

/** @brief automation/link struct */
typedef struct {
	cd_link_t id;			   /** @brief automation id (also used as handle) */
	cd_e_automation_type type; /** @brief automation type/action */
	cd_s_node *button;		   /** @brief pointer to node with button */
	cd_s_node *light;		   /** @brief pointer to node with light */
	bool valid;				   /** @brief whether .button and .light are valid pointers (complete automation) */
} cd_s_automation;

/**
 * @brief mesh network connector
 *
 * handles communication with the border router over a serial connection and
 * exposes current network state through structured data (as defined above).
 *
 * the terms link and automation are used interchangibly. a set of automation
 * rules is called the configuration. nodes are sometimes referred to as light
 * or button when that specific part of a node is used. the terms
 * (gui-specific) id's and handles are also used interchangibly.
 */
class CDMeshConnector {
private:
	/** @brief list of links */
	map<cd_link_t, cd_s_automation *> _links;
	/** @brief list of nodes */
	map<cd_uid_t, cd_s_node *> _nodes;

	cd_link_t _fresh_link_id = 0;
	cd_uid_t _fresh_node_id	 = 0;

	/** @brief get 'fresh' link id and increment */
	virtual cd_link_t get_new_link_id();
	/** @brief get 'fresh' node id and increment */
	virtual cd_uid_t get_new_node_id();

	/** @brief register a node to this class (GUI only) */
	virtual cd_uid_t create_node(cd_s_node node);
	/** @brief unregister a node from this class (GUI only) */
	virtual void remove_node(cd_uid_t node_handle);

public:
	CDMeshConnector();
	virtual ~CDMeshConnector();

	// (UNUSED/UNIMPLEMENTED) refresh functions
	/** @brief [UNIMPL] force refresh network node list */
	virtual void refresh_nodes_sync();
	/** @brief [UNIMPL] force refresh network automation configuration */
	virtual void refresh_config_sync();

	// data fetching functions
	/**
	 * @brief get map of automations and their respective handles
	 *
	 * @param valid  `valid` field of automation needs to match this value. `true` by default
	 */
	virtual map<cd_link_t, cd_s_automation *> get_links(bool valid = true);
	/**
	 * @brief get map of nodes and their respective handles
	 *
	 * @param provisioned  `provisioned` field of node needs to match this value. `false` by default
	 */
	virtual map<cd_uid_t, cd_s_node *> get_nodes(bool provisioned = false);
	/** @brief get automation pointer by automation id */
	virtual cd_s_automation *get_link(cd_link_t id);
	/** @brief get node pointer by node id */
	virtual cd_s_node *get_node(cd_uid_t id);
	virtual cd_uid_t get_or_create_node_by_uuid(cd_uuid_t uuid);
	virtual cd_link_t get_or_create_link_by_uuid(cd_uuid_t button, cd_uuid_t light);

	// network modification functions
	/** @brief create empty automation */
	virtual cd_link_t create_link();
	/**
	 * @brief create valid automation with filled-in fields and update on
	 * network.
	 *
	 * @param button  node id for node whose button will be used for this automation.
	 * @param light  node id for node whose light will be used for this automation.
	 * @param action  action/automation type (toggle, on, off).
	 */
	virtual cd_link_t create_link(cd_uid_t button, cd_uid_t light, cd_e_automation_type action);
	/**
	 * @brief overwrite link id with new automation and update on network.
	 *
	 * `automation` needs to be a globally available pointer to an automation
	 * (e.g. one allocated using malloc()). used to update existing automation
	 * properties.
	 *
	 * @param automation  pointer to automation struct (with new/modified values)
	 * @param publish  `true` to send POST_LINK command
	 */
	virtual void update_link(cd_s_automation *automation, bool publish = false);
	/**
	 * @brief remove automation and update on network.
	 *
	 * @param link_handle  automation id
	 * @param publish  `true` to send POST_LINK command
	 */
	virtual void remove_link(cd_link_t link_handle, bool publish = false);

	/**
	 * @brief overwrite node id with new node and update on network.
	 *
	 * `node` needs to be a globally available pointer to a node (e.g. one
	 * allocated using malloc()). used to update existing node properties.
	 *
	 * @param node_ptr  pointer to node struct (with new/modified state)
	 * @param publish  `true` to send POST_LED command
	 */
	virtual void update_node(cd_s_node *node_ptr, bool publish = false);
	/**
	 * @brief provision node into network
	 *
	 * @param node_ptr  pointer to node struct
	 */
	virtual void network_join_node(cd_s_node *node_ptr);
	/**
	 * @brief provision node out of network (remove from network)
	 *
	 * @param node_ptr  pointer to node struct
	 */
	virtual void network_remove_node(cd_s_node *node_ptr);

	// conversion functions
	/** @brief convert `cd_mac_addr_t` to `std::string` for printing/GUI */
	static string cd_mac_to_string(cd_mac_addr_t mac);
	/** @brief convert `cd_uuid_t` to `std::string` for printing/GUI */
	static string cd_uuid_to_string(cd_uuid_t uuid);
};

/** @brief global pointer to mesh connector, initialized in CDMainWindow */
extern CDMeshConnector *g_cd_mesh_connector;
