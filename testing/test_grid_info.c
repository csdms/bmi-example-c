#include <heat/bmi_heat.h>
#include <bmi/bmilib.h>
#include <heat/heat.h>

#include <stdio.h>
#include <stdlib.h>

void print_var_info (BMI_Model *model, const char *var);

int
main (void)
{
  BMI_Model *model = (BMI_Model*)malloc (sizeof(BMI_Model));

  register_bmi_heat(model);

  BMI_Initialize (model, NULL);

  {
    char name[BMI_MAX_COMPONENT_NAME];
    BMI_Get_component_name (model, name);
    fprintf (stdout, "%s\n", name);
  }

  { /* Input items */
    int n_names;
    char **names = NULL;
    int i;

    BMI_Get_input_var_name_count(model, &n_names);

    names = (char**) malloc (sizeof(char*) * n_names);
    for (i = 0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof (char) * BMI_MAX_VAR_NAME);

    BMI_Get_input_var_names (model, names);
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

    BMI_Get_output_var_name_count(model, &n_names);

    names = (char**) malloc (sizeof(char*) * n_names);
    for (i = 0; i<n_names; i++)
      names[i] = (char*) malloc (sizeof (char) * BMI_MAX_VAR_NAME);

    BMI_Get_output_var_names (model, names);
    fprintf(stdout, "no names is %d\n", n_names); fflush(stdout);
    for (i = 0; i<n_names; i++)
      print_var_info (model, names[i]);

    for (i = 0; i<n_names; i++)
      free (names[i]);
    free (names);
  }

  BMI_Finalize (model);

  free (model);

  return EXIT_SUCCESS;
}

void
print_var_info (BMI_Model *model, const char *var)
{
  char type[BMI_MAX_TYPE_NAME];
  char units[BMI_MAX_UNITS_NAME];
  int n_dims;
  int *shape;
  double *spacing;
  double *origin;
  int grid;

  BMI_Get_var_grid (model, var, &grid);
  BMI_Get_var_type (model, var, type);
  BMI_Get_var_units (model, var, units);
  BMI_Get_grid_rank (model, grid, &n_dims);

  shape = (int*) malloc (sizeof (int)*n_dims);
  spacing = (double*) malloc (sizeof (double)*n_dims);
  origin = (double*) malloc (sizeof (double)*n_dims);

  BMI_Get_grid_shape (model, grid, shape);
  BMI_Get_grid_spacing (model, grid, spacing);
  BMI_Get_grid_origin (model, grid, origin);

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
