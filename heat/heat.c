#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heat.h"

#define OK (0)
#define NOT_OK (1)


int initialize_arrays (HeatModel *self);


HeatModel *
heat_from_input_file (const char * filename)
{
  HeatModel * self = NULL;

  {
    FILE *fp = NULL;
    double alpha = 0.;
    double t_end = 1.;
    int n_x = 0;
    int n_y = 0;

    fp = fopen (filename, "r");
    if (!fp)
      return NULL;
    else
      self = (HeatModel*) malloc (sizeof(HeatModel));

    fscanf (fp, "%lf, %lf, %d, %d", &alpha, &t_end, &n_x, &n_y);

    self->dt = 1. / (4. * alpha);
    self->alpha = alpha;
    self->t_end = t_end;
    self->shape[0] = n_y;
    self->shape[1] = n_x;
  }

  self->spacing[0] = 1.;
  self->spacing[1] = 1.;

  initialize_arrays (self);

  return self;
}

HeatModel *
heat_from_default (void)
{
  HeatModel * self = (HeatModel*) malloc (sizeof(HeatModel));

  if (self) {
    self->alpha = 1.;
    self->t_end = 10.;
    self->shape[0] = 10;
    self->shape[1] = 20;
    self->spacing[0] = 1.;
    self->spacing[1] = 1.;
    self->dt = 1. / (4. * self->alpha);
  }
  else
    return NULL;

  initialize_arrays (self);

  return self;
}


int
initialize_arrays (HeatModel *self)
{
  if (self) {
    int i;
    const int n_rows = self->shape[0];
    const int n_cols = self->shape[1];
    const int n_elements = n_rows * n_cols;
    double top_x = self->shape[1] - 1;

    /* Allocate memory */
    self->z = (double **)malloc (sizeof (double*) * n_rows);
    self->temp_z = (double **)malloc (sizeof (double*) * n_rows);

    if (!self->temp_z || !self->z)
      return NOT_OK;

    self->z[0] = (double *)malloc (sizeof (double) * n_elements);
    self->temp_z[0] = (double *)malloc (sizeof (double) * n_elements);

    if (!self->temp_z[0] || !self->z[0])
      return NOT_OK;

    for (i=1; i<n_rows; i++) {
      self->z[i] = self->z[i-1] + n_cols;
      self->temp_z[i] = self->temp_z[i-1] + n_cols;
    }

    self->t = 0;
    for (i = 0; i < n_elements; i++)
      self->z[0][i] = rand ()*1./RAND_MAX * top_x * top_x * .5 - top_x * top_x * .25;
    for (i = 0; i < n_rows; i++) {
      self->z[i][0] = 0.;
      self->z[i][n_cols-1] = 0.;
    }
    for (i = 0; i < n_cols; i++) {
      self->z[0][i] = 0.;
      self->z[n_rows-1][i] = top_x*top_x*.25 - (i-top_x*.5) * (i-top_x*.5);
    }
    
    memcpy (self->temp_z[0], self->z[0], sizeof (double) * n_elements);
  }
  else
    return 1;

  return OK;
}


int
heat_free (HeatModel *self)
{
  if (self) {
    free (self->temp_z[0]);
    free (self->temp_z);
    free (self->z[0]);
    free (self->z);
    free (self);
  }
  return OK;
}


int
heat_advance_in_time (HeatModel * self)
{
  if (self) {
    const int n_elements = self->shape[0] * self->shape[1];

    heat_solve_2d (self->z, self->shape, self->spacing, self->alpha,
        self->dt, self->temp_z);
    self->t += self->dt;
    memcpy (self->z[0], self->temp_z[0], sizeof (double) * n_elements);
  }
  else
    return NOT_OK;

  return OK;
}


int
heat_solve_2d (double ** z, int shape[2], double spacing[2], double alpha,
    double dt, double ** out)
{
  {
    int i, j;
    const int top_row = shape[0] - 1;
    const int top_col = shape[1] - 1;
    const double dx2 = spacing[1] * spacing[1];
    const double dy2 = spacing[0] * spacing[0];
    const double c = alpha * dt / (dx2 + dy2);

    for (i=1; i<top_row; i++)
      for (j=1; j<top_col; j++)
        out[i][j] = c * (dx2 * (z[i][j - 1] + z[i][j + 1]) +
                         dy2 * (z[i - 1][j] + z[i + 1][j]) -
                         2. * (dx2 + dy2) * z[i][j]);

    for (j=0; j<shape[1]; j++) {
        out[0][j] = 0.;
        out[top_row][j] = 0.;
    }
    for (i=0; i<shape[0]; i++) {
        out[i][0] = 0.;
        out[i][top_col] = 0.;
    }

    for (i=1; i<top_row; i++)
      for (j=1; j<top_col; j++)
        out[i][j] += z[i][j];
  }

  return OK;
}
