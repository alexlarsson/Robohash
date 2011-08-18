#include <stdio.h>
#include <robohash.h>

int
main (int argc, char *argv[])
{
  GdkPixbuf *pixbuf;

  g_type_init ();

  if (argc < 3) {
    fprintf (stderr, "Usage test-robohash <string> <png filename>\n");
    exit (1);
  }

  pixbuf = robohash_create_hash (0, argv[1], 48, 48);
  gdk_pixbuf_save (pixbuf, argv[2], "png", NULL, NULL);
}
