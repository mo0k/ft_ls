/*
**	struct dirent 
**	{
**	    ino_t          d_ino;        numéro d'inœud 
**	    off_t          d_off;        décalage jusqu'à la dirent suivante 
**	    unsigned short d_reclen;     longueur de cet enregistrement 
**	    unsigned char  d_type;       type du fichier 
**	    char           d_name[256];  nom du fichier 
**	};
**_____________________________________________________________________________________________________
**
** 	int	stat(const char *restrict path, struct stat *restrict buf);
**
**	struct stat 
**	{
**    	dev_t     st_dev;       ID du périphérique contenant le fichier
**    	ino_t     st_ino;       Numéro inœud
**   	mode_t    st_mode;      Protection
**    	nlink_t   st_nlink;     Nb liens matériels
**   	uid_t     st_uid;     	UID propriétaire 
**    	gid_t     st_gid;       GID propriétaire 
**    	dev_t     st_rdev;      ID périphérique (si fichier spécial) 
**    	off_t     st_size;      Taille totale en octets 
**    	blksize_t st_blksize;   Taille de bloc pour E/S 
**    	blkcnt_t  st_blocks;    Nombre de blocs alloués 
**    	time_t    st_atime;     Heure dernier accès 
**    	time_t    st_mtime;     Heure dernière modification 
**    	time_t    st_ctime;     Heure dernier changement état 
**	};
**
**	st_mode
**
**	S_IFMT	  0170000	masque du type de fichier
**	S_IFSOCK  0140000	socket
**	S_IFLNK	  0120000	lien symbolique
**	S_IFREG	  0100000	fichier ordinaire
**	S_IFBLK	  0060000	périphérique blocs
**	S_IFDIR	  0040000	répertoire
**	S_IFCHR	  0020000	périphérique caractères
**	S_IFIFO	  0010000	fifo
**	S_ISUID	  0004000	bit set-UID
**	S_ISGID	  0002000	bit set-GID (voir plus loin)
**	S_ISVTX	  0001000	bit « sticky » (voir plus loin)
**	S_IRWXU		00700	lecture/écriture/exécution du propriétaire
**	S_IRUSR		00400	le propriétaire a le droit de lecture
**	S_IWUSR		00200	le propriétaire a le droit d'écriture
**	S_IXUSR		00100	le propriétaire a le droit d'exécution
**	S_IRWXG		00070	lecture/écriture/exécution du groupe
**	S_IRGRP		00040	le groupe a le droit de lecture
**	S_IWGRP		00020	le groupe a le droit d'écriture
**	S_IXGRP		00010	le groupe a le droit d'exécution
**	S_IRWXO		00007	lecture/écriture/exécution des autres
**	S_IROTH		00004	les autres ont le droit de lecture
**	S_IWOTH		00002	les autres ont le droit d'écriture
**	S_IXOTH		00001	les autres ont le droit d'exécution
**
**__________________________________________________________________________________
**
**	struct passwd *getpwuid(uid_t uid);
**
**	struct passwd 
**	{
**		char    *pw_name;        user name 
**		char    *pw_passwd;      encrypted password 
**		uid_t   pw_uid;          user uid 
**		gid_t   pw_gid;          user gid 
**		time_t  pw_change;       password change time 
**		char    *pw_class;       user access class 
**		char    *pw_gecos;       Honeywell login info 
**		char    *pw_dir;         home directory 
**		char    *pw_shell;       default shell 
**		time_t  pw_expire;       account expiration 
**		int     pw_fields;       internal: fields filled in 
**	};
**
**__________________________________________________________________________________
**
**	struct group *getgrgid(gid_t gid);
**
**	struct group 
**	{
**		char    *gr_name;        group name 
**		char    *gr_passwd;      group password 
**		gid_t   gr_gid;          group id 
**		char    **gr_mem;        group members 
**	};
*/

#include <ft_ls.h>

int		main(int ac, char **av)
{
	t_opts *all_options;
	t_opts *options;
	t_lst_all *lst_root;
	t_lst_all *tmp;
	t_print_func print_func;

	all_options = (t_opts*)malloc(sizeof(t_opts));
	all_options->sort = ft_strdup("tr");
	all_options->display = ft_strdup("Ral1");
	options = NULL;
	lst_root = NULL;
	if (!(lst_root = check_input(ac, av, all_options, &options)))
		return (1);
	print_func = get_print_func(options);
	tmp = lst_root;
	print_root_file(lst_root->t_file, options, print_func);
	if(!(browse_first_node(&tmp->t_dir, options, print_func)))
		return (1);
	del_options(&all_options);
	del_options(&options);
	free(lst_root);
	//while(1){};
	return (0);
}

/*
** ALIGNEMENT
**
**	42               Pearson          Projets archives SRVm0k           Training         forClaire        workspace-Qt
**	Projets archives Projets archives Projets archives Projets archives Projets archives Projets archives 
**
**	Desktop       Developpement Documents     Downloads     Library       Movies        Music         Pictures      Public        Qt
**	Developpement Developpement Developpement Developpement Developpement Developpement Developpement Developpement Developpement 
*/