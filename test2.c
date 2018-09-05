#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	char			data;
	struct s_list	*next;
}				t_list;


t_list	*ft_create_elem(char data)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (elem != NULL)
	{
		elem->data = data;
		elem->next = NULL;
	}
	return (elem);
}
 
void	ft_list_push_back(t_list **first_line, char data)
{
	t_list	*elem;

	if (first_line && *first_line)
	{
		elem = *first_line;
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = ft_create_elem(data);
	}
	else
		*first_line = ft_create_elem(data);
}

int main()
{
    t_list *first_line;
    
	first_line = ft_create_elem('b');
    ft_list_push_back(&first_line, 'a');
    printf("%c\n", first_line->data);

    return 0;
}
