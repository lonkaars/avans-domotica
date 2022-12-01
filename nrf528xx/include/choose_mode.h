

#ifndef CHOOSE_MODE_H__
#define CHOOSE_MODE_H__

#include <zephyr/bluetooth/mesh.h>


#ifdef __cplusplus
extern "C" {
#endif
/** normal working node. it has 2 clients and 2 servers if possible.*/
void normal_node();

/** provisioning node. it communicates to unprovisioned devices and makes them prov*/
void prov_node();

#ifdef __cplusplus
}
#endif

#endif /* MODEL_HANDLER_H__ */