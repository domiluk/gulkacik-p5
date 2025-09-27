#include <alogg.h>
#include <string.h>

#define DATASZ  (1<<15) /* (32768) amount of data to read from disk each time */
#define BUFSZ   (1<<16) /* (65536) size of audiostream buffer */


typedef struct {
  PACKFILE *f;
  ALOGG_OGGSTREAM *s;
} OGGFILE;


OGGFILE *open_ogg_file(char *filename) {
  OGGFILE *p = NULL;
  PACKFILE *f = NULL;
  ALOGG_OGGSTREAM *s = NULL;
  char data[DATASZ];
  int len;

  if (!(p = (OGGFILE *)malloc(sizeof(OGGFILE))))
    goto error;
  if (!(f = pack_fopen(filename, F_READ)))
    goto error;
  if ((len = pack_fread(data, DATASZ, f)) <= 0)
    goto error;
  if (len < DATASZ) {
    if (!(s = alogg_create_oggstream(data, len, TRUE)))
      goto error;
  }
  else {
    if (!(s = alogg_create_oggstream(data, DATASZ, FALSE)))
      goto error;
  }
  p->f = f;
  p->s = s;
  return p;

  error:
  pack_fclose(f);
  free(p);
  return NULL;
}


int play_ogg_file(OGGFILE *ogg, int buflen, int vol, int pan) {
  return alogg_play_oggstream(ogg->s, buflen, vol, pan);
}


void close_ogg_file(OGGFILE *ogg) {
  if (ogg) {
    pack_fclose(ogg->f);
    alogg_destroy_oggstream(ogg->s);
    free(ogg);
  }
}


int poll_ogg_file(OGGFILE *ogg) {
  char *data;
  long len;

  data = (char *)alogg_get_oggstream_buffer(ogg->s);
  if (data) {
    len = pack_fread(data, DATASZ, ogg->f);
    if (len < DATASZ)
      alogg_free_oggstream_buffer(ogg->s, len);
    else
      alogg_free_oggstream_buffer(ogg->s, -1);
  }

  return alogg_poll_oggstream(ogg->s);
}
