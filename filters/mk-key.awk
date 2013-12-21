# $Header: /usr/build/vile/vile/filters/RCS/mk-key.awk,v 1.2 2000/03/16 23:37:16 tom Exp $
#
# Generate makefile rules for vile's keywords files, i.e., to install/uninstall.
# Basically we want to install all of the .key files as .keywords, but cannot
# use awk to derive the list from the genmake.mak file because there is not a
# one-one correspondence between filter programs and keyword files.  Awk has
# no feature for testing if the files actually exist - so we simply install
# what we have.

BEGIN	{
		first = 1;
		count = 0;
		total = 0;
	}
	!/^#/ {
		if (first) {
			strip = from "/filters/";
			first = 0;
			print ""
			print "# Rules generated by filters/mk-key.awk"
		}
		name = substr($1, length(strip) + 1, length($1) - length(strip));
		src[count] = sprintf("$(srcdir)/%s", name);
		dst[count] = sprintf("$(DATADIR)/%swords", name);
		count++;
	}
END	{
		printf "INSTALL_TEXT =";
		for (i = 0; i < count; i++) {
			printf " \\\n\t%s", dst[i];
		}
		print ""
		print ""
		print "install :: $(INSTALL_TEXT)"
		print ""
		print "uninstall ::"
		printf "\t-$(RM) $(INSTALL_TEXT)\n"
		print ""

		for (i = 0; i < count; i++) {
			printf "%s :\t", dst[i];
			if ( length(dst[i]) < 22 )
				printf "\t";
			printf "%s ; ", src[i];
			if ( length(src[i]) < 22 )
				printf "\t";
			printf "$(INSTALL_DATA) $? $@\n"
		}
	}
