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
	DIR *tmp;
	struct dirent *x;
	(void)ac;

	t_lst_file *lst;

	lst = NULL;

	tmp = opendir(av[1]);
	if (tmp == NULL)
	{
		if (errno == ENOTDIR)
		{
			if (file_stat(".", av[1], &lst))
			{
				//printf("OK\n");
				return (0);
			}
			printf("LALALLALAL\n");
		}
		perror("ft_ls: ");
		return (1);
	}
	

	
	while ((x = readdir(tmp)))
	{
		//printf("________________________________\n");
		if (file_stat(av[1], x->d_name, &lst))
		{
			//printf("OK\n");
		}
		else
		{
			printf("KO\n");
			return (1);
		}
	}
	//printf("1: %s %s %s  %s %s %s %s\n", lst->permi, lst->lnk, lst->owner, lst->group, lst->size, lst->date, lst->name);
	set_padding(&lst);
	print_lst(lst);
	//printf("2: %s %s %s  %s %s %s %s\n", lst->permi, lst->lnk, lst->owner, lst->group, lst->size, lst->date, lst->name);

	if (closedir(tmp) == -1)
	{
		printf("ERROR closedir\n");
		return (1);
	}
	//while(1) {};
	return (0);
}

char *get_permi(char *nbr, mode_t	m)
{
	char *ret;
	char *tmp;
	int i;
	int j;

	j = 0;
	i = 0;
	ret = ft_strnew(10);
	
	ret[i++] = get_filetype(m);
	tmp = ret + 1;
	while (i < 10)
	{
		tmp = ft_memmove(tmp, convert_permi(nbr[j++]), 3);
		i += 3;
		tmp += 3;
	}
	return (ret);
}

char *convert_permi(char nbr)
{
	//printf("HEREE => nbr:%d\n", nbr);
	if (nbr == '0')
		return ("---");
	if (nbr == '1')
		return ("--x");
	if (nbr == '2')
		return ("-w-");
	if (nbr == '3')
		return ("-wx");
	if (nbr == '4')
		return ("r--");
	if (nbr == '5')
		return ("r-x");
	if (nbr == '6')
		return ("rw-");
	if (nbr == '7')
		return ("rwx");
	else
		return (NULL);
}

char 	get_filetype(mode_t	m)
{
	if (S_ISLNK(m))
		return ('l');
	else if (S_ISREG(m))
		return ('-');
	else if (S_ISDIR(m))
		return ('d');
	else if (S_ISCHR(m))
		return ('c');
	else if (S_ISBLK(m))
		return ('b');
	else if (S_ISFIFO(m))
		return ('p');
	else if (S_ISSOCK(m))
		return ('s');
	else
		return(0);
}

int 	file_stat(char *path, char *filename, t_lst_file **lst)
{
	struct stat s;
	char *test1;
	char *test2;
	char *filepath;
	char *tmp_path;
	t_lst_file *tmp;

	if (!(filepath = ft_strjoin((tmp_path = verif_filepath(path)), filename)))
		return (-1);
	free(tmp_path);
	if (lstat(filepath, &s) == -1)
	{
		perror("stat");
		free(filepath);
		return (0);
	}
	else
	{
		tmp = *lst;
		tmp = add_lst(lst);
		if (!(test1 = ft_itoa_base(s.st_mode, "01234567")))
			return (0);
		tmp->permi = get_permi(test1 + (ft_strlen(test1) - 3), s.st_mode);
		free(test1);
		tmp->lnk = ft_itoa((int)s.st_nlink);
		tmp->owner = getpwuid(s.st_uid)->pw_name;
		tmp->group = getgrgid(s.st_gid)->gr_name;
		tmp->size = ft_itoa((int)s.st_size);
		tmp->date = ft_strsub(ctime(&s.st_mtime), 4, 12);
		tmp->name = filename;
		//ft_putnbr(s.st_nlink);
		//printf("%s\n", *lst->date);
	}
	free(filepath);
	return (1);
}

char	*verif_filepath(char *path)
{
	if (!path)
		return (NULL);
	if (path[(int)ft_strlen(path) - 1] == '/')
		return (ft_strdup(path));
	else
		return (ft_strjoin(path, "/"));
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