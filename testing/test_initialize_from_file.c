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
  model->self = new_bmi_heat();

  {
    fprintf (stdout, "Initializing... ");

    status = model->initialize(model->self, "config.txt");
    if (status == BMI_FAILURE)
      return BMI_FAILURE;

    fprintf (stdout, "PASS\n");
  }

  {
    char name[BMI_MAX_COMPONENT_NAME];

    status = model->get_component_name(model->self, name);
    if (status == BMI_FAILURE)
      return BMI_FAILURE;

    fprintf (stdout, "%s\n", name);
  }

  {
    double dt, t_end;

    status = model->get_time_step(model->self, &dt);
    if (status == BMI_FAILURE)
      return BMI_FAILURE;
    else
      fprintf (stdout, "Time step dt = %f\n", dt);

    status = model->get_end_time(model->self, &t_end);
    if (status == BMI_FAILURE)
      return BMI_FAILURE;
    else
      fprintf (stdout, "End time t_end = %f\n", t_end);
  }

  fprintf (stdout, "Finalizing... ");

  status = model->finalize(model->self);
  if (status == BMI_FAILURE)
    return BMI_FAILURE;

  fprintf (stdout, "PASS\n");

  free (model);

  return BMI_SUCCESS;
}
