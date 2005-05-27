// expect.
//
//  --check turns on checking that the working tree matches the
//    files that are being modified, but doesn't apply the patch
//  --stat does just a diffstat, and doesn't actually apply
//  --show-files shows the directory changes
//
static int diffstat = 0;
static int check = 0;
static int apply = 1;
static int show_files = 0;
static const char apply_usage[] = "git-apply [--stat] [--check] [--show-files] <patch>";

/*
 * For "diff-stat" like behaviour, we keep track of the biggest change
 * we've seen, and the longest filename. That allows us to do simple
 * scaling.
 */
static int max_change, max_len;

struct fragment {
	unsigned long oldpos, oldlines;
	unsigned long newpos, newlines;
	const char *patch;
	int size;
	struct fragment *next;
};

struct patch {
	char *new_name, *old_name, *def_name;
	unsigned int old_mode, new_mode;
	int is_rename, is_copy, is_new, is_delete;
	int lines_added, lines_deleted;
	struct fragment *fragments;
	struct patch *next;
};
static void parse_traditional_patch(const char *first, const char *second, struct patch *patch)
		patch->is_new = 1;
		patch->is_delete = 0;
		name = find_name(second, NULL, p_value, TERM_SPACE | TERM_TAB);
		patch->new_name = name;
		patch->is_new = 0;
		patch->is_delete = 1;
		name = find_name(first, NULL, p_value, TERM_EXIST | TERM_SPACE | TERM_TAB);
		patch->old_name = name;
		name = find_name(first, NULL, p_value, TERM_EXIST | TERM_SPACE | TERM_TAB);
		patch->old_name = patch->new_name = name;
static int gitdiff_hdrend(const char *line, struct patch *patch)
static int gitdiff_oldname(const char *line, struct patch *patch)
	patch->old_name = gitdiff_verify_name(line, patch->is_new, patch->old_name, "old");
static int gitdiff_newname(const char *line, struct patch *patch)
	patch->new_name = gitdiff_verify_name(line, patch->is_delete, patch->new_name, "new");
static int gitdiff_oldmode(const char *line, struct patch *patch)
	patch->old_mode = strtoul(line, NULL, 8);
static int gitdiff_newmode(const char *line, struct patch *patch)
	patch->new_mode = strtoul(line, NULL, 8);
static int gitdiff_delete(const char *line, struct patch *patch)
	patch->is_delete = 1;
	patch->old_name = patch->def_name;
	return gitdiff_oldmode(line, patch);
static int gitdiff_newfile(const char *line, struct patch *patch)
	patch->is_new = 1;
	patch->new_name = patch->def_name;
	return gitdiff_newmode(line, patch);
static int gitdiff_copysrc(const char *line, struct patch *patch)
	patch->is_copy = 1;
	patch->old_name = find_name(line, NULL, 0, 0);
static int gitdiff_copydst(const char *line, struct patch *patch)
	patch->is_copy = 1;
	patch->new_name = find_name(line, NULL, 0, 0);
static int gitdiff_renamesrc(const char *line, struct patch *patch)
	patch->is_rename = 1;
	patch->old_name = find_name(line, NULL, 0, 0);
static int gitdiff_renamedst(const char *line, struct patch *patch)
	patch->is_rename = 1;
	patch->new_name = find_name(line, NULL, 0, 0);
static int gitdiff_similarity(const char *line, struct patch *patch)
static int gitdiff_unrecognized(const char *line, struct patch *patch)
static char *git_header_name(char *line)
{
	int len;
	char *name, *second;

	/*
	 * Find the first '/'
	 */
	name = line;
	for (;;) {
		char c = *name++;
		if (c == '\n')
			return NULL;
		if (c == '/')
			break;
	}

	/*
	 * We don't accept absolute paths (/dev/null) as possibly valid
	 */
	if (name == line+1)
		return NULL;

	/*
	 * Accept a name only if it shows up twice, exactly the same
	 * form.
	 */
	for (len = 0 ; ; len++) {
		char c = name[len];

		switch (c) {
		default:
			continue;
		case '\n':
			break;
		case '\t': case ' ':
			second = name+len;
			for (;;) {
				char c = *second++;
				if (c == '\n')
					return NULL;
				if (c == '/')
					break;
			}
			if (second[len] == '\n' && !memcmp(name, second, len)) {
				char *ret = xmalloc(len + 1);
				memcpy(ret, name, len);
				ret[len] = 0;
				return ret;
			}
		}
	}
	return NULL;
}

static int parse_git_header(char *line, int len, unsigned int size, struct patch *patch)
	patch->is_new = 0;
	patch->is_delete = 0;

	/*
	 * Some things may not have the old name in the
	 * rest of the headers anywhere (pure mode changes,
	 * or removing or adding empty files), so we get
	 * the default name from the header.
	 */
	patch->def_name = git_header_name(line + strlen("diff --git "));
			int (*fn)(const char *, struct patch *);
			if (p->fn(line + oplen, patch) < 0)
static int parse_num(const char *line, unsigned long *p)

	if (!isdigit(*line))
		return 0;
	*p = strtoul(line, &ptr, 10);
	return ptr - line;
}

static int parse_range(const char *line, int len, int offset, const char *expect,
			unsigned long *p1, unsigned long *p2)
{
	digits = parse_num(line, p1);
	if (!digits)
	*p2 = *p1;
	if (*line == ',') {
		digits = parse_num(line+1, p2);
		if (!digits)
			return -1;

		offset += digits+1;
		line += digits+1;
		len -= digits+1;
	}

static int parse_fragment_header(char *line, int len, struct fragment *fragment)
	offset = parse_range(line, len, 4, " +", &fragment->oldpos, &fragment->oldlines);
	offset = parse_range(line, len, offset, " @@", &fragment->newpos, &fragment->newlines);
static int find_header(char *line, unsigned long size, int *hdrsize, struct patch *patch)
	patch->is_rename = patch->is_copy = 0;
	patch->is_new = patch->is_delete = -1;
	patch->old_mode = patch->new_mode = 0;
	patch->old_name = patch->new_name = NULL;
			struct fragment dummy;
			if (parse_fragment_header(line, len, &dummy) < 0)
			int git_hdr_len = parse_git_header(line, len, size, patch);
			if (!patch->old_name && !patch->new_name)
				die("git diff header lacks filename information");
		parse_traditional_patch(line, line+len, patch);
static int parse_fragment(char *line, unsigned long size, struct patch *patch, struct fragment *fragment)
	int added, deleted;
	offset = parse_fragment_header(line, len, fragment);
	oldlines = fragment->oldlines;
	newlines = fragment->newlines;
	if (patch->is_new < 0 && (pos[0] || oldlines))
		patch->is_new = 0;
	if (patch->is_delete < 0 && (pos[1] || newlines))
		patch->is_delete = 0;
	added = deleted = 0;
			deleted++;
			added++;
		/* We allow "\ No newline at end of file" */
		case '\\':
			break;
	patch->lines_added += added;
	patch->lines_deleted += deleted;
static int parse_single_patch(char *line, unsigned long size, struct patch *patch)
	struct fragment **fragp = &patch->fragments;
		struct fragment *fragment;
		int len;

		fragment = xmalloc(sizeof(*fragment));
		memset(fragment, 0, sizeof(*fragment));
		len = parse_fragment(line, size, patch, fragment);
		fragment->patch = line;
		fragment->size = len;

		*fragp = fragment;
		fragp = &fragment->next;
static int parse_chunk(char *buffer, unsigned long size, struct patch *patch)
	int offset = find_header(buffer, size, &hdrsize, patch);

	patchsize = parse_single_patch(buffer + offset + hdrsize, size - offset - hdrsize, patch);

	return offset + hdrsize + patchsize;
}

const char pluses[] = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
const char minuses[]= "----------------------------------------------------------------------";

static void show_stats(struct patch *patch)
{
	char *name = patch->old_name;
	int len, max, add, del;

	if (!name)
		name = patch->new_name;

	/*
	 * "scale" the filename
	 */
	len = strlen(name);
	max = max_len;
	if (max > 50)
		max = 50;
	if (len > max)
		name += len - max;
	len = max;

	/*
	 * scale the add/delete
	 */
	max = max_change;
	if (max + len > 70)
		max = 70 - len;
	
	add = (patch->lines_added * max + max_change/2) / max_change;
	del = (patch->lines_deleted * max + max_change/2) / max_change;
	printf(" %-*s |%5d %.*s%.*s\n",
		len, name, patch->lines_added + patch->lines_deleted,
		add, pluses, del, minuses);
}

static int check_patch(struct patch *patch)
{
	struct stat st;
	const char *old_name = patch->old_name;
	const char *new_name = patch->new_name;

	if (old_name) {
		int pos = cache_name_pos(old_name, strlen(old_name));
		int changed;

		if (pos < 0)
			return error("%s: does not exist in index", old_name);
		if (patch->is_new < 0)
			patch->is_new = 0;
		if (lstat(old_name, &st) < 0)
			return error("%s: %s\n", strerror(errno));
		changed = ce_match_stat(active_cache[pos], &st);
		if (changed)
			return error("%s: does not match index", old_name);
		if (!patch->old_mode)
			patch->old_mode = st.st_mode;
	}

	if (new_name && (patch->is_new | patch->is_rename | patch->is_copy)) {
			return error("%s: already exists in index", new_name);
		if (!lstat(new_name, &st))
			return error("%s: already exists in working directory", new_name);
		if (errno != ENOENT)
			return error("%s: %s", new_name, strerror(errno));
	return 0;
}
static int check_patch_list(struct patch *patch)
{
	int error = 0;
	for (;patch ; patch = patch->next)
		error |= check_patch(patch);
	return error;
}

static void show_file(int c, unsigned int mode, const char *name)
{
	printf("%c %o %s\n", c, mode, name);
}

static void show_file_list(struct patch *patch)
{
	for (;patch ; patch = patch->next) {
		if (patch->is_rename) {
			show_file('-', patch->old_mode, patch->old_name);
			show_file('+', patch->new_mode, patch->new_name);
			continue;
		}
		if (patch->is_copy || patch->is_new) {
			show_file('+', patch->new_mode, patch->new_name);
			continue;
		}
		if (patch->is_delete) {
			show_file('-', patch->old_mode, patch->old_name);
			continue;
		}
		if (patch->old_mode && patch->new_mode && patch->old_mode != patch->new_mode) {
			printf("M %o:%o %s\n", patch->old_mode, patch->new_mode, patch->old_name);
			continue;
		}
		printf("M %o %s\n", patch->old_mode, patch->old_name);
	}
}

static void stat_patch_list(struct patch *patch)
{
	int files, adds, dels;

	for (files = adds = dels = 0 ; patch ; patch = patch->next) {
		files++;
		adds += patch->lines_added;
		dels += patch->lines_deleted;
		show_stats(patch);
	}

	printf(" %d files changed, %d insertions(+), %d deletions(-)\n", files, adds, dels);
}

static void patch_stats(struct patch *patch)
{
	int lines = patch->lines_added + patch->lines_deleted;

	if (lines > max_change)
		max_change = lines;
	if (patch->old_name) {
		int len = strlen(patch->old_name);
		if (len > max_len)
			max_len = len;
	}
	if (patch->new_name) {
		int len = strlen(patch->new_name);
		if (len > max_len)
			max_len = len;
	}
	struct patch *list = NULL, **listp = &list;
		struct patch *patch;
		int nr;

		patch = xmalloc(sizeof(*patch));
		memset(patch, 0, sizeof(*patch));
		nr = parse_chunk(buffer + offset, size, patch);
		patch_stats(patch);
		*listp = patch;
		listp = &patch->next;

	if ((check || apply) && check_patch_list(list) < 0)
		exit(1);

	if (show_files)
		show_file_list(list);

	if (diffstat)
		stat_patch_list(list);

		if (!strcmp(arg, "--stat")) {
			apply = 0;
			diffstat = 1;
			continue;
		}
		if (!strcmp(arg, "--check")) {
			apply = 0;
			check = 1;
			continue;
		}
		if (!strcmp(arg, "--show-files")) {
			show_files = 1;
			continue;
		}