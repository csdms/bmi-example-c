#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <heat.h>
#include <bmi.h>
#include <bmi_heat.h>


int
main (void)
{
  int status = BMI_SUCCESS;
  Bmi * model = (Bmi*)malloc (sizeof(Bmi));

  register_bmi_heat(model);

  {
    int i;
    const int n_steps = 3;

    for (i = 0; i < n_steps; i++)
    {
      fprintf (stdout, "Reinitialize %d\n", i+1);

      fprintf (stdout, "Initializing... ");
      status = model->initialize(model, NULL);
      if (status == BMI_FAILURE)
        return BMI_FAILURE;
      else
        fprintf(stdout, "PASS\n");

      {
        char name[BMI_MAX_COMPONENT_NAME];

        status = model->get_component_name(model, name);
        if (status == BMI_FAILURE)
	        return BMI_FAILURE;
        else
          fprintf(stdout, "%s\n", name);
      }

      fprintf (stdout, "Finalizing... ");
      status = model->finalize(model);
      if (status == BMI_FAILURE)
        return BMI_FAILURE;
      else
        fprintf(stdout, "PASS\n");
    }
  }

  free(model);

  return BMI_SUCCESS;
}
