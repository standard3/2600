#include <stdio.h>
#include "walktreeid.h"
#include "walktreeid_traversal.h"

void wkt_preorder_show(treeid root)
{
    // X puis Y puis Z
    // On traite le noeud en cours puis respectivement sa partie gauche, puis droite.

    if (root != 0)
    {
        printf("%c\n", wkt_get_char(root));
        wkt_preorder_show(wkt_get_left(root));
        wkt_preorder_show(wkt_get_right(root));
    }
}

void wkt_postorder_show(treeid root)
{
    // Y puis Z puis X
    // On traite respectivement la partie gauche, puis droite du noeud en cours, puis finalement celui-ci.

    if (root != 0)
    {
        wkt_postorder_show(wkt_get_left(root));
        wkt_postorder_show(wkt_get_right(root));
        printf("%c\n", wkt_get_char(root));
    }
}

void wkt_inorder_show(treeid root)
{
    // Y puis X puis Z
    // On traite la partie gauche du noeud courant, puis le noeud lui-même, et enfin de sa partie droite.

    if (root != 0)
    {
        wkt_inorder_show(wkt_get_left(root));
        printf("%c\n", wkt_get_char(root));
        wkt_inorder_show(wkt_get_right(root));
    }
}
