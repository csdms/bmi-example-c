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

    status = model->initialize(model, "config.txt");
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
    double dt, t_end;

    status = model->get_time_step(model, &dt);
    if (status == BMI_FAILURE)
      return BMI_FAILURE;
    else
      fprintf (stdout, "Time step dt = %f\n", dt);

    status = model->get_end_time(model, &t_end);
    if (status == BMI_FAILURE)
      return BMI_FAILURE;
    else
      fprintf (stdout, "End time t_end = %f\n", t_end);
  }

  fprintf (stdout, "Finalizing... ");

  status = model->finalize(model);
  if (status == BMI_FAILURE)
    return BMI_FAILURE;

  fprintf (stdout, "PASS\n");

  free (model);

  return BMI_SUCCESS;
}
