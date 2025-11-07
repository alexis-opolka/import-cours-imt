#include <stdio.h>
#include <string.h>

enum ResultCode {
  ok = 0,
  compte_non_trouve = 1,
  solde_insuffisant = 2
};
static char* ResulCodetStrings[] = {
  "Ok", "Compte non trouvé", "Solde insuffisant"
};
typedef enum ResultCode ResultCode;

union ErreurInfo {
  char* account_name;
  int* account_value;
};
typedef union ErreurInfo ErreurInfo;

struct Result {
  int account_number;
  ResultCode exit_status;
  ErreurInfo error_info;
};
typedef struct Result Result;

void affiche_erreur(Result* erreur) {
  printf("Erreur: %s\n", ResulCodetStrings[erreur->exit_status]);
}

void affiche_erreur_extensive(Result* erreur) {
  if (erreur->exit_status == compte_non_trouve) {

    // Si le compte est non trouvé, on affiche l'erreur, avec le nom recherché
    printf("Erreur: Compte %s non trouvé !\n", erreur->error_info.account_name);
  } else if (erreur->exit_status == solde_insuffisant) {

    // Si le solde est insuffisant, on affiche l'erreur, avec le solde
    printf("Erreur: Solde insuffisant, vous n'avez que %d sur votre compte !\n", *erreur->error_info.account_value);
  }
}

/**
  Cette fonction trouve un compte dans la liste des comptes en utilisant le nom de l'utilisateur
  Elle renvoie la position du compte dans la liste des comptes
*/
Result trouver_compte(int nombre_comptes, char** comptes_user, char* user_a_trouver){
  // This is the fallback result, if not found, the members are not changed
  Result result = {.account_number = -1, .exit_status = compte_non_trouve, .error_info.account_name = user_a_trouver};

  for (int i = 0; i < nombre_comptes; i++){
    if (strcmp(comptes_user[i], user_a_trouver) == 0){
      // We update the result struct to send back the correct values
      result.account_number = i;
      result.exit_status = ok;
    }
  }


  return result;
}

/**
  Cette fonction permet de déposer de l'argent sur un compte
  Elle renvoie l'identifiant du compte sur lequel l'argent à été trouvé et -1 si il n'a pas été trouvé ou si le solde était insuffisant
*/
Result retrait_argent(int nombre_comptes, int* comptes_id, int* comptes_solde, char** comptes_users, char* user){
  Result result = {.account_number = -1, .exit_status = solde_insuffisant};

  printf("quel est le montant du retrait ?");

  int montant;
  scanf("%d", &montant);

  Result compte = trouver_compte(nombre_comptes, comptes_users, user);
  if (compte.exit_status == compte_non_trouve){
    // We forward the return result from trouver_compte
    // to this function's result
    result = compte;
  } else {
    // We handled the case where the account number was undefined
    // then we can assign it to the result struct
    result.account_number = compte.account_number;

    if (comptes_solde[compte.account_number] > montant){
      // We update the result struct with the correct exit status
      comptes_solde[compte.account_number] -= montant;
      result.exit_status = ok;
    } else {
      // Here just in case we have an issue that wasn't handled properly
      result.error_info.account_value = &comptes_solde[compte.account_number];
    }
  }

  return result;
}


int main(){
  int comptes_id[3] = {5, 12, 7};
  int comptes_soldes[3] = {500, 60, 12700};
  char* comptes_users[3] = {"mlk", "fdm", "sdb"};

  while (1){
    char nom_compte[4];
    int id_compte;
    char operation;

    // Getting a name
    printf("veuillez entrer votre nom\n");
    scanf(" %c%c%c", nom_compte, nom_compte + 1, nom_compte + 2);

    nom_compte[3] = 0;

    // Getting the operation requested
    printf("quelle opération souhaitez vous effectuer ?"
      "\n\tTapez a pour afficher votre solde"
      "\n\tTapez r pour effectuer un retrait"
      "\n\tTapez q pour quitter ce shell\n");
    scanf(" %c", &operation);

    if (operation == 'a'){
      Result compte = trouver_compte(3, comptes_users, nom_compte);

      if (compte.exit_status == compte_non_trouve){
        affiche_erreur_extensive(&compte);

        printf("Erreur: votre compte n'a pas été trouvé\n");
      } else {
        printf("Le solde de votre compte est : %d\n", comptes_soldes[compte.account_number]);
      }
    } else if (operation == 'r'){
      Result result = retrait_argent(3, comptes_id, comptes_soldes, comptes_users, nom_compte);

      if (result.exit_status == solde_insuffisant){
        affiche_erreur_extensive(&result);

        printf("erreur lors du retrait, l'opération n'a pas été effectuée\n");
      } else {
        printf("la somme a bien été retirée du compte n° %d\n", result.account_number);
      }
    } else if (operation == 'q') {

      printf("Centaurustasie's Bank at your service, Goodbye!\n");
      break;
    } else {

      printf("Unrecognized operation! Please try again.\n");
    }
  }
}

