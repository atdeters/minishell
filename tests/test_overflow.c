#include "../src/minishell.h"

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (8);
	return (0);
}

// Make this one actually check properly
bool	lloverflow(const char *str)
{
	if (ft_strlen(str) > 20)
		return (true);
	if (ft_strlen(str) == 20 && ft_isnum(str[0]))
		return (true);
	if (ft_strlen(str) == 20 && str[0] == '-')
	{
		if (ft_strncmp(str, "-9223372036854775808", 20) > 0)
			return (true);
	}
	if (ft_strlen(str) == 20 && str[0] == '+')
	{
		if (ft_strncmp(str, "+9223372036854775807", 20) > 0)
			return (true);
	}
	if (ft_strlen(str) == 19 && ft_isnum(str[0]))
	{
		if (ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (true);
	}
	return (false);
}

int	main(void)
{
	char *str1 = "-9223372036854775808";
	char *str2 = "-9223372036854775809";
	char *str3 = "+9223372036854775807";
	char *str4 = "+9223372036854775808";
	char *str5 = "9223372036854775807";
	char *str6 = "9223372036854775808";
	char *str7 = "0";
	char *str8 = "+10";
	char *str9 = "-10";
	char *str10 = "10";
	
	printf("%s does overflow: %s\n", str1, lloverflow(str1) ? "true" : "false");
	printf("%s does overflow: %s\n", str2, lloverflow(str2) ? "true" : "false");
	printf("%s does overflow: %s\n", str3, lloverflow(str3) ? "true" : "false");
	printf("%s does overflow: %s\n", str4, lloverflow(str4) ? "true" : "false");
	printf("%s does overflow: %s\n", str5, lloverflow(str5) ? "true" : "false");
	printf("%s does overflow: %s\n", str6, lloverflow(str6) ? "true" : "false");
	printf("%s does overflow: %s\n", str7, lloverflow(str7) ? "true" : "false");
	printf("%s does overflow: %s\n", str8, lloverflow(str8) ? "true" : "false");
	printf("%s does overflow: %s\n", str9, lloverflow(str9) ? "true" : "false");
	printf("%s does overflow: %s\n", str10, lloverflow(str10) ? "true" : "false");

}