#include "my_parser.h"
#define _POSIX_C_SOURCE 202404L
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LOG(...) fprintf(stderr, __VA_ARGS__);

struct parser           *new_parser(const char *content)
{
    struct parser       *p = calloc(1, sizeof (*p));
    p->content = content;
    return p;
}

void                    clean_parser(struct parser *p)
{
    free(p);
}

int                    count_lines(struct parser *p, struct position *pos)
{
    pos->line = 1;
    pos->col = 1;
    for (int idx = 0; idx < p->last_pos; idx += 1)
    {
        if (p->content[idx] == '\n')
        {
            pos->line += 1;
            pos->col = 1;
        }
        else
            pos->col += 1;
    }
    return 1;
}

int                     reset_pos(struct parser *p, int tmp)
{
    p->current_pos = tmp;
    return 1;
}

char                    *get_line_error(struct parser *p)
{
    // cherche le début de la ligne
    int begin = p->last_pos;
    for (; begin > 0; begin -= 1)
        if (p->content[begin] == '\n')
        {
            begin += 1;
            break;
        }
    // cherche la fin de la ligne
    int end = p->last_pos;
    for (; p->content[end]; end += 1)
        if (p->content[end] == '\n')
            break;
    // extrait la sous-chaine
    fprintf(stderr, "CUT %d %d\n", begin, end);
    int sz = end - begin;
    char *sub = malloc(sz + 1);
    memcpy(sub, &p->content[begin], sz);
    sub[sz] = 0;
    return sub;
}

int                     readeof(struct parser *p)
{
    return p->content[p->current_pos] == 0;
}

static inline void      nextpos(struct parser *p)
{
    p->current_pos += 1;
    if (p->current_pos > p->last_pos)
        p->last_pos = p->current_pos;
}

// TODO

int                     readchar(struct parser *p, char c)
{
    if (p->content[p->current_pos] == c)
    {
        nextpos(p);
        return 1;
    }

    return 0;
}

int                     readrange(struct parser *p, char begin, char end)
{
    // current_post should be between begin and end
    if (p->content[p->current_pos] >= begin
    &&  p->content[p->current_pos] <= end)
    {
        nextpos(p);
        return 1;
    }

    return 0;
}

int                     readtext(struct parser *p, char *text)
{
    while (*text != '\0')
    {
        if (p->content[p->current_pos] != *text)
            return 0;
        nextpos(p);
        text++;
    }

    return 1;
}

// [0-9]+
int                     readint(struct parser *p)
{
    if (readrange(p, '0', '9')) {
        while (readrange(p, '0', '9'))
            ;
        return 1;
    }
    return 0;
}

// [a-zA-Z_][a-zA-Z_0-9]*
int                     readid(struct parser *p)
{
    int tmp = p->current_pos;

    // first char should be in [a-zA-Z_]
    if (!readrange(p, 'a', 'z')
    &&  !readrange(p, 'A', 'Z')
    &&  !readchar(p, '_'))
        return 0;

    // next chars should be in [a-zA-Z_0-9]
    while (1)
    {
        if (!readrange(p, 'a', 'z')
        &&  !readrange(p, 'A', 'Z')
        &&  !readrange(p, '0', '9')
        &&  !readchar(p, '_'))
        {
            if (tmp == p->current_pos) return 0;
            else return 1;
        }
    }
}

/*
    Float <- ('-' / '+')* (Dec / Frac) Exp?

    Dec <- Int '.' Int?

    Frac <- '.' Int

    Exp <- ('e' / 'E') ('-' / '+')? Int

    Int <- [0-9]+
*/

static int              readfloat_dec(struct parser *p)
{
    if (readint(p) && readchar(p, '.'))
    {
        readint(p);
        return 1;
    }

    return 0;
}
static int              readfloat_frac(struct parser *p)
{
    if (readchar(p, '.') && readint(p))
        return 1;

    return 0;
}
static int              readfloat_exp(struct parser *p)
{
    if (readchar(p, 'e') || readchar(p, 'E'))
    {
        (void) (readchar(p, '-') || readchar(p, '+'));
        if (readint(p))
            return 1;
    }

    return 0;
}
int                     readfloat(struct parser *p)
{
    while (readchar(p, '-') || readchar(p, '+'))
        ;

    if (readfloat_dec(p) || readfloat_frac(p)) {
        (void) readfloat_exp(p);
        return 1;
    }

    return 0;
}

// 2ieme partie - manipulation d'AST

int                     push_node_context(struct parser *p)
{
    struct capture_list    *_ = calloc(1, sizeof (*_));
    LOG("PUSH _ NODE CTX _:%p prev:%p\n", (void*)_, (void*)p->nodes);
    _->name = "_";
    _->prev = p->nodes;
    p->nodes = _;
    return 1;
}

int                     pop_node_context(struct parser *p)
{
    struct capture_list *it = p->nodes;
    LOG("POP NODE CTX FROM here nodes:%p\n", (void*)it);
    while (it)
    {
        struct capture_list    *current = it;
        it = it->prev;
        int b = 0;
        if (it)
            b = strcmp(current->name, "_") == 0;

        LOG("FREE NODE %p (%s) - prev %p\n", (void*)current, current->name, (void*)it);
	if (current->data)
            free(current->data);
        free(current);
        if (b)
            break;
    }
    LOG("RESET TO NODE %p\n", (void*)it);
    p->nodes = it;
    return 1;
}

int                    move_node_data(struct capture_list *dst, struct capture_list *src)
{
    LOG("SET NODE %p from %p\n", (void*)dst, (void*)src);
    dst->data = src->data;
    src->data = 0;
    return 1;
}

struct capture_list	*get_node(struct parser *p, const char *node_name)
{
    struct capture_list *it = p->nodes;
    while (it)
    {
        if (strcmp(it->name, node_name) == 0)
            return it;
        it = it->prev;
    }
    return NULL;
}

char                    *get_value(struct parser *p, const struct capture_list *node)
{
    char *res = strndup(&p->content[node->begin], node->end - node->begin);
    return res;
}

int                     begin_capture(struct parser *p, const char *tagname)
{
    struct capture_list *item = calloc(1, sizeof (*item));
    item->prev = p->nodes;
    p->nodes = item;
    item->name = tagname;
    item->begin = p->current_pos;
    return 1;
}

int                     end_capture(struct parser *p, const char *tagname)
{
    struct capture_list *item = get_node(p, tagname);
    printf("END CAPTURE %p\n", (void*)item);
    item->end = p->current_pos;
    return 1;
}
