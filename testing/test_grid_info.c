#include <stdio.h>
#include <stdlib.h>

#include <heat.h>
#include <bmi.h>
#include <bmi_heat.h>


void print_var_info (Bmi *model, const char *var);

int
main (void)
{
  Bmi *model = (Bmi*)malloc (sizeof(Bmi));

  register_bmi_heat(model);

  model->initialize(model, NULL);

  {
    char name[BMI_MAX_COMPONENT_NAME];
    model->get_component_name(model, name);
    fprintf (stdout, "%s\n", name);
  }

  { /* Input items */
    int n_names;
    char **names = NULL;
    int i;

    model->get_input_item_count(model, &n_names);

    names = (char**) malloc (sizeof(char*) * n_names);
    for (i = 0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof (char) * BMI_MAX_VAR_NAME);

    model->get_input_var_names(model, names);
    for (i = 0; i<n_names; i++)
      print_var_info (model, names[i]);

    for (i = 0; i<n_names; i++)
      free (names[i]);
    free (names);
  }

  { /* Output items */
    int n_names;
    char **names = NULL;
    int i;

    model->get_output_item_count(model, &n_names);

    names = (char**) malloc (sizeof(char*) * n_names);
    for (i = 0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof (char) * BMI_MAX_VAR_NAME);

    model->get_output_var_names(model, names);
    fprintf(stdout, "no names is %d\n", n_names); fflush(stdout);
    for (i = 0; i<n_names; i++)
      print_var_info (model, names[i]);

    for (i = 0; i<n_names; i++)
      free (names[i]);
    free (names);
  }

  model->finalize(model);

  free (model);

  return EXIT_SUCCESS;
}

void
print_var_info (Bmi *model, const char *var)
{
  char type[BMI_MAX_TYPE_NAME];
  char units[BMI_MAX_UNITS_NAME];
  int n_dims;
  int *shape;
  double *spacing;
  double *origin;
  int grid;

  model->get_var_grid(model, var, &grid);
  model->get_var_type(model, var, type);
  model->get_var_units(model, var, units);
  model->get_grid_rank(model, grid, &n_dims);

  shape = (int*) malloc (sizeof (int)*n_dims);
  spacing = (double*) malloc (sizeof (double)*n_dims);
  origin = (double*) malloc (sizeof (double)*n_dims);

  model->get_grid_shape(model, grid, shape);
  model->get_grid_spacing(model, grid, spacing);
  model->get_grid_origin(model, grid, origin);

  fprintf (stdout, "\n");
  fprintf (stdout, "Variable info\n");
  fprintf (stdout, "=============\n");
  fprintf (stdout, "Name: %s\n", var);
  fprintf (stdout, "Type: %s\n", type);
  fprintf (stdout, "Units: %s\n", units);
  fprintf (stdout, "Rank: %d\n", n_dims);
  fprintf (stdout, "Dimension: %d x %d\n", shape[0], shape[1]);
  fprintf (stdout, "Resolution: %f x %f\n", spacing[0], spacing[1]);
  fprintf (stdout, "Corner: %f x %f\n", origin[0], origin[1]);

  free (origin);
  free (spacing);
  free (shape);

  return;
}
