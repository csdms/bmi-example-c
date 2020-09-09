#include <stdio.h>
#include <stdlib.h>

#include <heat.h>
#include <bmi.h>
#include <bmi_heat.h>


void print_var_values(Bmi *model, const char *var_name);

int
main (void)
{
  double *new_vals = NULL;
  int err = 0;
  Bmi * model = (Bmi*)malloc (sizeof(Bmi));

  register_bmi_heat(model);

  err = model->initialize(model, NULL);
  if (err)
    return EXIT_FAILURE;

  {
    char name[BMI_MAX_COMPONENT_NAME];
    model->get_component_name(model, name);
  
    fprintf (stdout, "%s\n", name);
  }

  { /* Get grid information */
    int n_dims;
    int *shape;
    int len = 0;
    int i;
    int grid;

    model->get_var_grid(model, "plate_surface__temperature", &grid);
    model->get_grid_rank(model, grid, &n_dims);
    shape = (int*) malloc (sizeof (int)*n_dims);

    model->get_grid_shape(model, grid, shape);
    for (i = 0, len = 1; i < n_dims; i++)
      len *= shape[i];

    new_vals = (double *)malloc (sizeof (double) * len);
    for (i = 0; i < len; i++)
      new_vals[i] = -1;

    free (shape);
  }

  fprintf (stdout, "Values before set\n");
  fprintf (stdout, "=================\n");
  print_var_values (model, "plate_surface__temperature");

  model->set_value(model, "plate_surface__temperature", new_vals);

  fprintf (stdout, "Values after set\n");
  fprintf (stdout, "================\n");
  print_var_values (model, "plate_surface__temperature");

  {
    int inds[5] = {1, 2, 4, 8, 16};
    double vals[5] = {11, 22, 44, 88, 1616};
    double *p;
    int i;

    model->set_value_at_indices(model, "plate_surface__temperature", inds, 5, vals);
    print_var_values (model, "plate_surface__temperature");

    model->get_value_ptr(model, "plate_surface__temperature", (void**)(&p));
    for (i=0; i<5; i++) {
      fprintf (stdout, "Checking %d...", inds[i]);
      if (p[inds[i]] == vals[i])
        fprintf (stdout, "PASS\n");
    }
  }

  free (new_vals);

  model->finalize(model);

  free (model);

  return EXIT_SUCCESS;
}

void
print_var_values(Bmi *model, const char *var_name)
{
  double *var = NULL;
  int n_dims = 0;
  int *shape = NULL;
  int grid;

  model->get_var_grid(model, var_name, &grid);
  model->get_grid_rank(model, grid, &n_dims);
  shape = (int*) malloc (sizeof (int)*n_dims);

  model->get_grid_shape(model, grid, shape);
  model->get_value_ptr(model, var_name, (void**)(&var));

  fprintf (stdout, "Variable: %s\n", var_name);
  fprintf (stdout, "Number of dimension: %d\n", n_dims);
  fprintf (stdout, "Shape: %d x %d\n", shape[0], shape[1]);
  fprintf (stdout, "================\n");

  {
    int i, j;
    for (i = 0; i < shape[0]; i++) {
      for (j = 0; j < shape[1]; j++)
        fprintf (stdout, "%f ", var[i*shape[1]+j]);
      fprintf (stdout, "\n");
    }
  }

  return;
}
