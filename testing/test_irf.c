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
    fprintf (stdout, "Initializing... ");
    fflush(stdout);

    status = model->initialize(model, NULL);
    if (status == BMI_FAILURE)
      return BMI_FAILURE;

    fprintf (stdout, "PASS\n");
  }

  {
    char name[BMI_MAX_COMPONENT_NAME];

    status = model->get_component_name(model, name);
    if (status == BMI_FAILURE)
      return BMI_FAILURE;

    fprintf (stdout, "%s\n", name);
  }

  {
    int i;
    const int n_steps = 10;
    double time;
    double dt;

    status = model->get_time_step(model, &dt);
    if (status == BMI_FAILURE)
      return BMI_FAILURE;

    for (i = 0; i < n_steps; i++)
    {
      fprintf (stdout, "Running until t = %d... ", i+1);

      status = model->update(model);
      if (status == BMI_FAILURE)
        return BMI_FAILURE;
      
      status = model->get_current_time(model, &time);
      if (status == BMI_FAILURE)
        return BMI_FAILURE;

      if (fabs (time / dt - (i + 1)) < 1e-6)
        fprintf (stdout, "PASS\n");
      else
        return BMI_FAILURE;
    }

    fprintf (stdout, "Running until t = %f... ", 1000.5);

    status = model->update_until(model, 1000.5);
    if (status == BMI_FAILURE)
      return BMI_FAILURE;

    status = model->get_current_time(model, &time);
    if (status == BMI_FAILURE)
      return BMI_FAILURE;

    if (fabs (time-1000.5) < 1e-6)
      fprintf (stdout, "PASS\n");
    else {
      fprintf (stdout, "%f\n", time);
      return BMI_FAILURE;
    }
  }

  fprintf (stdout, "Finalizing... ");

  status = model->finalize(model);
  if (status == BMI_FAILURE)
    return BMI_FAILURE;

  fprintf (stdout, "PASS\n");

  free (model);

  return BMI_SUCCESS;
}
