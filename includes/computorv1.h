typedef struct		s_duo
{
	char			*str;
	double			value;
	double			power;
	struct s_lst	*next;
}					t_duo;

typedef struct		s_expr
{
	char			*str;
	char			**elems;
}					t_expr;

typedef struct		s_env
{
	char			*tmp;
	char			*minimized;
	t_expr			e1;
	t_expr			e2;
}					t_env;

#define MAX_INT 2147483647
#define MIN_INT 2147483648

#define OUT_COLOR "\e[0m"
#define PURPLE_COLOR "\e[1;35m"
#define RED_COLOR "\e[1;31m"
#define WHITE_COLOR "\e[1;29m"

#define WRONG_ARGS_NB RED_COLOR"error: "OUT_COLOR""WHITE_COLOR"wrong number of arguments\n"OUT_COLOR
#define WRONG_ARGS_NB_LEN 55
#define WRONG_DOUBLE_POINTS RED_COLOR"error: "OUT_COLOR""WHITE_COLOR"double point(s) detected :\n"OUT_COLOR
#define WRONG_DOUBLE_POINTS_LEN 56
#define WRONG_EQUALITY_1 RED_COLOR"error: "OUT_COLOR""WHITE_COLOR"no equality :\n"OUT_COLOR
#define WRONG_EQUALITY_1_LEN 43
#define WRONG_EQUALITY_2 RED_COLOR"error: "OUT_COLOR""WHITE_COLOR"too many equalities :\n"OUT_COLOR
#define WRONG_EQUALITY_2_LEN 51
#define WRONG_LAST RED_COLOR"error: "OUT_COLOR""WHITE_COLOR"invalid last :\n"OUT_COLOR
#define WRONG_LAST_LEN 44
#define WRONG_POWER RED_COLOR"error: "OUT_COLOR""WHITE_COLOR"invalid power :\n"OUT_COLOR
#define WRONG_POWER_LEN 45
#define WRONG_SPLIT PURPLE_COLOR"warning: "OUT_COLOR""WHITE_COLOR"splitted value(s) :\n"OUT_COLOR
#define WRONG_SPLIT_LEN 51
#define WRONG_POWER_VALUE RED_COLOR"error: "OUT_COLOR""WHITE_COLOR"invalid power value(s) :\n"OUT_COLOR
#define WRONG_POWER_VALUE_LEN 54

#define OUT_BNBN OUT_COLOR"\n\n"
#define OUT_BNBN_LEN 5

#define BN_ENTER_RED "\n"RED_COLOR
#define BN_ENTER_RED_LEN 8
#define BN_ENTER_PURPLE "\n"PURPLE_COLOR
#define BN_ENTER_PURPLE_LEN 8

int		ft_verifs2(char *line, char error, char warning);
int		ft_verifs(int ac, char *line);

int		ft_checkequalities(char *str);
int		ft_checklast(char *str);
int		ft_invalidlast(char *str);
int		ft_checkpowers(char *str);
int		ft_invalidpower(char *str);

int		ft_splittedval(char *str);
int		ft_checksplittedval(char *str);
int		ft_invalidsplittedval(char *str);
int		ft_checkpowervalue(char *str);
int		ft_invalidpowersvalue(char *str);

int		ft_error(char n);
int		ft_warning(char n);
int		ft_checkval(char *str);
int		ft_checkextremval(char *str);
int		ft_invalidextrem(char *str);


int		ft_nextsign(char *str);
int		ft_invalidpowerssign(char *str);
int		ft_checkpowerssign(char *str);
int		ft_invalidcharacters(char *str);
int		ft_checkcharacters(char *str);

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		ft_putnbr(int n);
void		ft_putstrarray(char **str);
void		*ft_memalloc(size_t size);
char		*ft_strnew(size_t size);

char		**ft_strsplit(char const *s, char c);

int			ft_split(t_env *e);
int			ft_parsing_error(char *str, char here, char asked);
char		*ft_getreduced(char *ptr);
void		ft_simplify(char **ptr);
char		*ft_simplified(char *str);