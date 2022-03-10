#ifndef VV_LIST_HEADER
#define VV_LIST_HEADER

typedef struct vv_node vv_node;
typedef struct vv_list vv_list;

struct vv_node {
	vv_node * next;
	vv_node * prev;
	void * data;
};

struct vv_list {
	vv_node 	* head;
	vv_node 	* tail;
	uint32_t	size;
};

vv_list * vv_list_initalize( void );
vv_node * vv_list_append( vv_list * list, void * node_data );
void vv_list_remove( vv_list * list, vv_node * node );
void vv_list_iterate( vv_list * list, void (*func)(vv_node *) );

#endif