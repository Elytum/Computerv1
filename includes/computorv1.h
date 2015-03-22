typedef struct		s_duo
{
	char			*str;
	long			value;
	long			power;
	struct s_lst	*next;
}					t_duo;

typedef struct		s_expr
{
	char			*str;
	char			**elems;
}					t_expr;

typedef struct		s_env
{
	char			*minimized;
	t_expr			e1;
	t_expr			e2;
}					t_env;