//X42 ?

typedef struct		s_duo
{
	double			value;
	double			power;
	struct s_duo	*next;
}					t_duo;

typedef struct		s_expr
{
	char			*str;
	t_duo			*elems;
}					t_expr;

typedef struct		s_env
{
	char			*tmp;
	char			*minimized;
	t_expr			e1;
	t_expr			e2;
	t_duo			*merged;
}					t_env;

union				powunion
{
	double			d;
	int				x[2];
};

typedef struct		s_values
{
	char			sign;
	double			v;
	struct s_values	*next;
}					t_values;

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
#define WRONG_POWER_SIGN RED_COLOR"error: "OUT_COLOR""WHITE_COLOR"invalid power sign(s) :\n"OUT_COLOR
#define WRONG_POWER_SIGN_LEN 53
#define WRONG_CHARACTERS RED_COLOR"error: "OUT_COLOR""WHITE_COLOR"invalid character(s) :\n"OUT_COLOR
#define WRONG_CHARACTERS_LEN 52
#define WRONG_EXTREM PURPLE_COLOR"warning: "OUT_COLOR""WHITE_COLOR"int limits overreached :\n"OUT_COLOR
#define WRONG_EXTREM_LEN 56
#define WRONG_OPERATORS RED_COLOR"warning: "OUT_COLOR""WHITE_COLOR"operators must be separed by numbers :\n"OUT_COLOR
#define WRONG_OPERATORS_LEN 70

//VALUES SEPARATORS : X * 2 * * 2

#define SINGLE_ERROR RED_COLOR"One error detected, can't process without correction\n"OUT_COLOR
#define SINGLE_ERROR_LEN 64
#define MULT_ERROR " errors detected, can't process without correction\n"OUT_COLOR
#define MULT_ERROR_LEN 57
#define SINGLE_WARNING PURPLE_COLOR"One warning detected, remember, answer might be wrong\n"OUT_COLOR
#define SINGLE_WARNING_LEN 65
#define MULT_WARNING " warnings detected, remember, answer might be wrong\n"OUT_COLOR
#define MULT_WARNING_LEN 56

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

int		ft_next_operation(char *str, int flag);

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void		ft_putnbr(int n);
void		ft_putstrarray(char **str);
void		*ft_memalloc(size_t size);
char		*ft_strnew_p(size_t size);

char		**ft_strsplit(char const *s, char c);

int			ft_split(t_env *e);
int			ft_parsing_error(char *str, char here, char asked);
char		*ft_getreduced(char *ptr);
void		ft_simplify(char **ptr);
char		*ft_simplified(char *str);

char		**ft_splitsigns(char *str);
t_duo		*ft_getduo(char *str);

double				ft_sqrt(const double fg);
double				ft_pow(double a, double b);