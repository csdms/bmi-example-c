#include <stdio.h>
#include <stdlib.h>

#include <heat.h>
#include <bmi.h>
#include <bmi_heat.h>


int
main (void)
{
  Bmi * model1 = (Bmi*)malloc (sizeof(Bmi));
  Bmi * model2 = (Bmi*)malloc (sizeof(Bmi));

  register_bmi_heat(model1);
  register_bmi_heat(model2);

  if (model1->initialize(model1, NULL) != BMI_SUCCESS || !model1)
    return BMI_FAILURE;
  else
    fprintf(stdout, "Model 1 initialized\n");

  if (model2->initialize(model2, NULL) != BMI_SUCCESS || !model2)
    return BMI_FAILURE;
  else
    fprintf(stdout, "Model 2 initialized\n");

  /* Does changing values in model1 change them in model2? */
  {
    char name[BMI_MAX_COMPONENT_NAME] = "plate_surface__temperature";
    int i;
    int inds[5] = {1, 2, 4, 8, 16};
    double vals[5] = {11, 22, 44, 88, 1616};
    double *p1, *p2;

    model1->get_value_ptr(model1, name, (void**)(&p1));
    fprintf(stdout, "Model 1 temperatures, initial...\n");
    for (i=0; i<5; i++) {
      fprintf (stdout, "%f ", p1[inds[i]]);
    }
    fprintf (stdout, "\n");

    model1->set_value_at_indices(model1, name, inds, 5, vals);
    fprintf(stdout, "Model 1 temperatures, changed...\n");
    for (i=0; i<5; i++) {
      fprintf (stdout, "%f ", p1[inds[i]]);
    }
    fprintf (stdout, "\n");

    model2->get_value_ptr(model2, name, (void**)(&p2));
    fprintf(stdout, "Model 2 temperatures...\n");
    for (i=0; i<5; i++) {
      fprintf (stdout, "%f ", p2[inds[i]]);
    }
    fprintf (stdout, "\n");

    for (i=0; i<5; i++) {
      if (p1[inds[i]] != p2[inds[i]])
        fprintf (stdout, "PASS ");
    }
    fprintf (stdout, "\n");
  }

  if (model1->finalize(model1) != BMI_SUCCESS)
    return BMI_FAILURE;
  else
    fprintf(stdout, "Model 1 finalized\n");

  if (model2->finalize(model2) != BMI_SUCCESS)
    return BMI_FAILURE;
  else
    fprintf(stdout, "Model 2 finalized\n");

  free(model1);
  free(model2);

  return BMI_SUCCESS;
}
