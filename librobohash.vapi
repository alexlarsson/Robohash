[CCode (cheader_filename = "robohash.h")]
namespace Robohash {
	[CCode (cname = "robohash_create_hash")]
	public Gdk.Pixbuf create_hash (int set, string data, int w, int h);
}
