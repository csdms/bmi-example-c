#include <heat/bmi_heat.h>

#include <stdio.h>
#include <stdlib.h>

void print_var_names (void *self);

int
main (void)
{
  void *self = NULL;

  if (BMI_HEAT_Initialize (NULL, &self)!=0 || !self)
    return EXIT_FAILURE;

  {
    char name[BMI_MAX_COMPONENT_NAME];
    BMI_HEAT_Get_component_name (self, name);
    fprintf (stdout, "%s\n", name);
  }

  print_var_names (self);

  if (BMI_HEAT_Finalize (self) != 0)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

void
print_var_names (void *self)
{
  { /* Print the input var names */
    int n_names;
    char **names = NULL;
    int i;

    BMI_HEAT_Get_input_var_name_count(self, &n_names);

    names = (char**) malloc (sizeof(char *) * n_names);
    for (i=0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);

    BMI_HEAT_Get_input_var_names (self, names);

    fprintf (stdout, "Input var names\n");
    fprintf (stdout, "===============\n");
    for (i = 0; i<n_names; i++)
      fprintf (stdout, "%s\n", names[i]);

    for (i=0; i<n_names; i++)
      free (names[i]);
    free (names);

  }

  fprintf (stdout, "\n");

  { /* Print the output var names */
    int n_names;
    char **names = NULL;
    int i;

    BMI_HEAT_Get_output_var_name_count(self, &n_names);

    names = (char**) malloc (sizeof(char *) * n_names);
    for (i=0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);

    BMI_HEAT_Get_output_var_names (self, names);

    fprintf (stdout, "Output var names\n");
    fprintf (stdout, "===============\n");
    for (i = 0; i<n_names; i++)
      fprintf (stdout, "%s\n", names[i]);

    for (i=0; i<n_names; i++)
      free (names[i]);
    free (names);

  }
}
