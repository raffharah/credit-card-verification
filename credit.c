#include <cs50.h>
#include <math.h>
#include <stdio.h>

int outros_digitos(long cartao_credito);
int multiandsoma(int ultimo_digito);
int numero_do_cartao(long cartao_credito);
bool amex_valido(long cartao_credito, int num_digitos);
bool master_valido(long cartao_credito, int num_digitos);
bool visa_valido(long cartao_credito, int num_digitos);

int main(void)
{
    long cartao_credito = get_long("Cartão de Crédito ");
    int soma_de_outros_digitos = outros_digitos(cartao_credito);
    int num_digitos = numero_do_cartao(cartao_credito);
    bool amex = amex_valido(cartao_credito, num_digitos);
    bool master = master_valido(cartao_credito, num_digitos);
    bool visa = visa_valido(cartao_credito, num_digitos);
    if (soma_de_outros_digitos % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    else if (amex == true)
    {
        printf("AMEX\n");
    }
    else if (master == true)
    {
        printf("MASTERCARD\n");
    }
    else if (visa == true)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}

bool amex_valido(long cartao_credito, int num_digitos)
{
    int primeiro_dois_digitos = cartao_credito / pow(10, 13);
    if ((num_digitos == 15) && (primeiro_dois_digitos == 34 || primeiro_dois_digitos == 37))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool master_valido(long cartao_credito, int num_digitos)
{
    int primeiro_dois_digitos = cartao_credito / pow(10, 14);
    if ((num_digitos == 16) && (primeiro_dois_digitos > 50 && primeiro_dois_digitos < 56))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool visa_valido(long cartao_credito, int num_digitos)
{
    if (num_digitos == 13)
    {
        int primeiro_digito = cartao_credito / pow(10, 12);
        if (primeiro_digito == 4)
        {
            return true;
        }
    }
    else if (num_digitos == 16)
    {
        int primeiro_digito = cartao_credito / pow(10, 15);
        if (primeiro_digito == 4)
        {
            return true;
        }
    }
    return false;
}

int numero_do_cartao(long cartao_credito)
{
    int conta = 0;
    while (cartao_credito > 0)
    {
        conta = conta + 1;
        cartao_credito = cartao_credito / 10;
    }
    return conta;
}

int outros_digitos(long cartao_credito)
{
    int soma = 0;
    bool digito_alternativo = false;
    while (cartao_credito > 0)
    {
        if (digito_alternativo == true)
        {
            int ultimo_digito = cartao_credito % 10;
            int produto = multiandsoma(ultimo_digito);
            soma = soma + produto;
        }
        else
        {
            int ultimo_digito = cartao_credito % 10;
            soma = soma + ultimo_digito;
        }

        digito_alternativo = !digito_alternativo;
        cartao_credito = cartao_credito / 10;
    }
    return soma;
}

int multiandsoma(int ultimo_digito)
{
    int multi = ultimo_digito * 2;
    int soma = 0;
    while (multi > 0)
    {
        int ultimo_digito_multi = multi % 10;
        soma = soma + ultimo_digito_multi;
        multi = multi / 10;
    }
    return soma;
}