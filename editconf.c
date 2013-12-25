#if OPT_EDITOR_CONFIG

#include <estruct.h>

#include <editorconfig/editorconfig.h>

static void
set_local_value(BUFFER *bp, const char *variable, const char *value)
{
    int status;
    VALARGS args;

    memset(&args, 0, sizeof(args));
    status = find_mode(bp, variable, FALSE, &args);
    if (set_mode_value(bp, variable, FALSE, TRUE, FALSE, &args, value) != TRUE) {
    }
}
void
editor_config_readhook(BUFFER *bp)
{
    editorconfig_handle eh;
    int err_num, name_value_count;
    int j;

    eh = editorconfig_handle_init();
    err_num = editorconfig_parse(bp->b_fname, eh);
    name_value_count = editorconfig_handle_get_name_value_count(eh);
    for (j = 0; j < name_value_count; ++j) {
	const char *name;
	const char *value;

	editorconfig_handle_get_name_value(eh, j, &name, &value);
	if (strcmp(name, "indent_style") == 0) {
	    if (strcmp(value, "space") == 0)
		set_local_value(bp, "tabinsert", "0");
	    else if (strcmp(value, "tab") == 0)
		set_local_value(bp, "tabinsert", "1");
	    else {
	    }
	} else if (strcmp(name, "indent_size") == 0) {
	    set_local_value(bp, "shiftwidth", value);
	} else if (strcmp(name, "tab_width") == 0) {
	    set_local_value(bp, "tabstop", value);
	} else if (strcmp(name, "end_of_line") == 0) {
	    if (strcmp(value, "lf") == 0)
		set_local_value(bp, "nl", "1");
	    else if (strcmp(value, "crlf") == 0)
		set_local_value(bp, "nl", "0");
	    else {
	    }
	}
    }
    editorconfig_handle_destroy(eh);
}

#endif
