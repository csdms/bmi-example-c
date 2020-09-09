#include <stdio.h>
#include <stdlib.h>

#include <heat.h>
#include <bmi.h>
#include <bmi_heat.h>


void print_var_names (Bmi *model);

int
main (void)
{
  Bmi * model = (Bmi*)malloc (sizeof(Bmi));

  register_bmi_heat(model);

  if (model->initialize(model, NULL) != BMI_SUCCESS || !model)
    return BMI_FAILURE;

  {
    char name[BMI_MAX_COMPONENT_NAME];
    model->get_component_name(model, name);
    fprintf(stdout, "%s\n\n", name);
  }

  print_var_names (model);

  if (model->finalize(model) != BMI_SUCCESS)
    return BMI_FAILURE;

  free (model);

  return BMI_SUCCESS;
}

void
print_var_names (Bmi *model)
{
  { /* Print the input var names */
    int n_names;
    char **names = NULL;
    int i;

    model->get_input_item_count(model, &n_names);

    names = (char**) malloc (sizeof(char *) * n_names);
    for (i=0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);

    model->get_input_var_names(model, names);

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

    model->get_output_item_count(model, &n_names);

    names = (char**) malloc (sizeof(char *) * n_names);
    for (i=0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);

    model->get_output_var_names(model, names);

    fprintf (stdout, "Output var names\n");
    fprintf (stdout, "================\n");
    for (i = 0; i<n_names; i++)
      fprintf (stdout, "%s\n", names[i]);

    for (i=0; i<n_names; i++)
      free (names[i]);
    free (names);

  }
}
