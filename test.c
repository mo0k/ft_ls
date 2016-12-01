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
*/

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int 	file_stat(char *path);

int		main(void)
{
	DIR *tmp;
	struct dirent *x;
	struct stat s;
	struct tm t;
	//__darwin_time_t t1;

	tmp = opendir(".");
	if (tmp == NULL)
	{
		perror("ft_ls: ");
		return (1);
	}
	while ((x = readdir(tmp)))
	{
		printf("________________________________\n");
		if (file_stat(x->d_name))
		{
			printf("OK\n");
		}
		else
		{
			printf("KO\n");
			return (1);
		}
	}
	if (closedir(tmp) == -1)
	{
		printf("ERROR closedir\n");
		return (1);
	}
	return (0);
}

int 	file_stat(char *filepath)
{
	struct stat s;
	if (stat(filepath, &s) == -1)
	{
		perror("stat");
		return (0);
	}
	else
	{
		printf("%s\n", filepath);
		printf("UID:%u\n", s.st_uid);
		printf("GID:%u\n", s.st_gid);
		printf("Size:%lld\n", s.st_size);
		printf("Taille de bloc d’E/S : %ld octets\n",(long) s.st_blksize);
		printf("Bloc alloues : %ld octets\n",(long) s.st_blocks);
		printf("Nombre links:%hu\n", s.st_nlink);
		printf("Dernier changement d’état :        %s", ctime(&s.st_ctime));
		printf("Dernier accès au fichier :         %s", ctime(&s.st_atime));
		printf("Dernière modification du fichier:  %s", ctime(&s.st_mtime));
		printf("yes\n");
	}
	return (1);
	
}