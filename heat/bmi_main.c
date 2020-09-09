#include <stdio.h>
#include <stdlib.h>

#include "heat.h"
#include <bmi.h>
#include "bmi_heat.h"


int main(int argc, char *argv[])
{
  Bmi *model = (Bmi *) malloc(sizeof(Bmi));

  if (argc != 2) {
    printf("Usage: run_bmiheatc CONFIGURATION_FILE\n\n");
    printf("Run the heatc model through its BMI with a configuration file.\n");
    printf("Output is written to the file `bmiheatc.out`.\n");
    return BMI_SUCCESS;
  }

  FILE *fp = fopen("bmiheatc.out", "w");
  fprintf(fp, "Configuration file = %s\n", argv[1]);

  register_bmi_heat(model);

  fprintf(fp, "Initializing... ");
  model->initialize(model, argv[1]);
  fprintf(fp, "done\n");

  {
    char model_name[BMI_MAX_COMPONENT_NAME];

    model->get_component_name(model, model_name);
    fprintf(fp, "%s\n", model_name);
  }

  {
    char *var_name = "plate_surface__temperature";
    int grid, rank, *shape;
    double *var = NULL;
    double time = 0.0;
    double end_time;

    fprintf(fp, "variable = %s\n", var_name);
    model->get_var_grid(model, var_name, &grid);

    model->get_grid_rank(model, grid, &rank);
    fprintf(fp, "rank = %d\n", rank);
    shape = (int *) malloc (sizeof(int) * rank);
    model->get_grid_shape(model, grid, shape);
    fprintf(fp, "shape = %d x %d\n", shape[0], shape[1]);

    model->get_value_ptr(model, var_name, (void **)(&var));
    
    model->get_end_time(model, &end_time);
    while (time < end_time) {
      model->get_current_time(model, &time);
      fprintf(fp, "\nTime = %f\n", time);

      {
        int i, j;
        for (i=0; i < shape[0]; i++) {
          for (j=0; j < shape[1]; j++) {
            fprintf(fp, "%6.2e ", var[i*shape[1] + j]);
          }
          fprintf(fp, "\n");
        }
      }

      model->update(model);
    }
  }
  
  fprintf(fp, "Finalizing... ");
  model->finalize(model);
  fprintf(fp, "done\n");

  free(model);
  fclose(fp);

  return BMI_SUCCESS;
}
