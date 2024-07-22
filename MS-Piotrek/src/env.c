// #include "minishell.h"

// void init_env_vars(t_gen *gen) {
//     gen->env_vars = NULL;
// }

// void add_env_var(t_gen *gen, const char *name, const char *value) {
//     t_env *new_var = malloc(sizeof(t_env));
//     if (!new_var) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     new_var->name = strdup(name);
//     new_var->value = strdup(value);
//     new_var->next = gen->env_vars;
//     gen->env_vars = new_var;
// }

// void builtin_env(t_gen *gen) {
//     t_env *current = gen->env_vars;
//     while (current != NULL) {
//         printf("%s=%s\n", current->name, current->value);
//         current = current->next;
//     }
// }