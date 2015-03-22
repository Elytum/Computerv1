typedef struct		s_duo
{
	char			*str;
	int				value;
	int				power;
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