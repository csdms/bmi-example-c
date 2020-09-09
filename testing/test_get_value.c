#include <stdio.h>
#include <stdlib.h>

#include <heat.h>
#include <bmi.h>
#include <bmi_heat.h>


void print_var_values(Bmi *model, const char *var_name);

int
main (void)
{
  int i;
  const int n_steps = 10;
  Bmi * model = (Bmi*)malloc (sizeof(Bmi));

  register_bmi_heat(model);

  model->initialize(model, NULL);

  {
    char name[BMI_MAX_COMPONENT_NAME];
    model->get_component_name(model, name);
    fprintf (stdout, "%s\n", name);
  }

  for (i = 0; i < n_steps; i++)
  {
    fprintf (stdout, "Values at time %d\n", i);
    fprintf (stdout, "==============\n");
    print_var_values (model, "plate_surface__temperature");

    model->update(model);
  }

  fprintf (stdout, "Values at time %d\n", i);
  fprintf (stdout, "==============\n");
  print_var_values (model, "plate_surface__temperature");

  model->finalize(model);

  free (model);

  return EXIT_SUCCESS;
}

void
print_var_values(Bmi *model, const char *var_name)
{
  double *var = NULL;
  int len;
  int rank;
  int *shape;
  int grid;

  model->get_var_grid(model, var_name, &grid);

  model->get_grid_rank(model, grid, &rank);
  fprintf (stderr, "rank = %d\n", rank);
  shape = (int*) malloc (sizeof (int) * rank);

  model->get_grid_shape(model, grid, shape);
  fprintf (stderr, "shape = %d x %d\n", shape[0], shape[1]);

  {
    int n;
    for (n = 0, len = 1; n < rank; n++)
      len *= shape[n];
  }

  var = (double*) malloc (sizeof (double)*len);

  model->get_value(model, var_name, var);

  fprintf (stdout, "Variable: %s\n", var_name);
  fprintf (stdout, "================\n");

  {
    int i, j;
    for (i = 0; i < shape[0]; i++) {
      for (j = 0; j < shape[1]; j++)
        fprintf (stdout, "%f ", var[i*shape[1] + j]);
      fprintf (stdout, "\n");
    }
  }

  free (var);
  free (shape);

  return;
}
