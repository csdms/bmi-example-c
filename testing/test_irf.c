#include <heat/bmi_heat.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main (void)
{
  void *self = NULL;
  int status = BMI_SUCCESS;

  {
    fprintf (stdout, "Initializing... ");

    status = BMI_HEAT_Initialize (NULL, &self);
    if (status == BMI_FAILURE || !self)
      return EXIT_FAILURE;

    fprintf (stdout, "PASS\n");
  }

  {
    char name[BMI_MAX_COMPONENT_NAME];

    status = BMI_HEAT_Get_component_name (self, name);
    if (status == BMI_FAILURE)
      return EXIT_FAILURE;

    fprintf (stdout, "%s\n", name);
  }

  {
    int i;
    const int n_steps = 10;
    double time;
    double dt;

    status = BMI_HEAT_Get_time_step(self, &dt);
    if (status == BMI_FAILURE)
      return EXIT_FAILURE;

    for (i = 0; i < n_steps; i++)
    {
      fprintf (stdout, "Running until t = %d... ", i+1);

      status = BMI_HEAT_Update (self);
      if (status == BMI_FAILURE)
        return EXIT_FAILURE;
      
      status = BMI_HEAT_Get_current_time (self, &time);
      if (status == BMI_FAILURE)
        return EXIT_FAILURE;

      if (fabs (time / dt - (i + 1)) < 1e-6)
        fprintf (stdout, "PASS\n");
      else
        return EXIT_FAILURE;
    }

    fprintf (stdout, "Running until t = %f... ", 1000.5);

    status = BMI_HEAT_Update_until (self, 1000.5);
    if (status == BMI_FAILURE)
      return EXIT_FAILURE;

    status = BMI_HEAT_Get_current_time (self, &time);
    if (status == BMI_FAILURE)
      return EXIT_FAILURE;

    if (fabs (time-1000.5) < 1e-6)
      fprintf (stdout, "PASS\n");
    else {
      fprintf (stdout, "%f\n", time);
      return EXIT_FAILURE;
    }
  }

  fprintf (stdout, "Finalizing... ");

  status = BMI_HEAT_Finalize (self);
  if (status == BMI_FAILURE)
    return EXIT_FAILURE;

  fprintf (stdout, "PASS\n");

  return EXIT_SUCCESS;
}
