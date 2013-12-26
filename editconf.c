#if OPT_EDITORCONFIG

#include <estruct.h>

#include <editorconfig/editorconfig.h>

static void
set_local_value(BUFFER *bp, const char *variable, const char *value)
{
    VALARGS args;

    memset(&args, 0, sizeof(args));
    if (find_mode(bp, variable, FALSE, &args) != TRUE) {
	mlforce("[Couldn't find variable %s]", variable);
	return;
    }
    if (set_mode_value(bp, variable, FALSE, TRUE, FALSE, &args, value) != TRUE) {
	mlforce("[Couldn't set variable %s]", variable);
	return;
    }
}

static void
set_local_boolean(BUFFER *bp, const char *variable, const char *value,
    const char *true_value, const char *false_value)
{
    if (strcmp(value, true_value) == 0)
    	set_local_value(bp, variable, "1");
    else if (strcmp(value, false_value) == 0)
    	set_local_value(bp, variable, "0");
    else
	mlforce("[Unexpected EditorConfig variable value: %s=%s]", variable, value);
}

void
editorconfig_readhook(BUFFER *bp)
{
    editorconfig_handle eh;
    int err_num;
    int name_value_count;
    int i;
    const char *name;
    const char *value;

    eh = editorconfig_handle_init();
    err_num = editorconfig_parse(bp->b_fname, eh);
    if (err_num != 0) {
	mlforce("[EditorConfig parse error: %s]", editorconfig_get_error_msg(err_num));
	return;
    }
    name_value_count = editorconfig_handle_get_name_value_count(eh);
    for (i = 0; i < name_value_count; ++i) {
	editorconfig_handle_get_name_value(eh, i, &name, &value);
	if (strcmp(name, "indent_style") == 0)
	    set_local_boolean(bp, "tabinsert", value, "tab", "space");
	else if (strcmp(name, "indent_size") == 0)
	    set_local_value(bp, "shiftwidth", value);
	else if (strcmp(name, "tab_width") == 0)
	    set_local_value(bp, "tabstop", value);
	else if (strcmp(name, "end_of_line") == 0)
	    set_local_value(bp, "recordseparator", value);
	else if (strcmp(name, "insert_file_newline") == 0)
	    set_local_boolean(bp, "newline", value, "true", "false");
	else
	    mlforce("[EditorConfig setting not supported: %s=%s]", name, value);
    }
    if (editorconfig_handle_destroy(eh) != 0)
	mlforce("[Error destroying EditorConfig handle]");
}

#endif
