#include <stdio.h>
#include <string.h>

int	ft_strcmp(char *s1, char *s2)
{
	int i;
	int res;

	res = 0;
	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == 0)
			return (0);
		i++;
	}
	res = s1[i] - s2[i];
	return (res);
}

int is_equal(char *s1, char *s2)
{
//	if (ft_strlen(s1) != strlen(s2))
//		return (0);
	if (ft_strcmp(s1, s2) != 0)
		return (0);
	return (1);
}


int main()
{
	char *s1= strdup("x11");
	char *s2 = strdup("x1");

	if(is_equal(s1, s2))
		printf("is equal!\n");
	else
		printf("is not equal!\n");

//	if (ft_strcmp(s2, s1) != 0)
//	{
//		printf("is not equal!\n");
//	}
//	else
//





}