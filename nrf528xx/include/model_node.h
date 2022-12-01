

#ifndef MODEL_NODE_H__
#define MODEL_NODE_H__

#include <zephyr/bluetooth/mesh.h>

#ifdef __cplusplus
extern "C" {
#endif

/** init for making a node. */
const struct bt_mesh_comp *model_node_init(void);

#ifdef __cplusplus
}
#endif

#endif /* MODEL_HANDLER_H__ */
