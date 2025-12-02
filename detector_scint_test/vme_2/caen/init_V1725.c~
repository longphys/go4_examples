/*************************************************************************/
/* init CAEN V1725 					                 */
/*                                                                       */
/*************************************************************************/

sprintf(c_line, "******************************\nCAEN 1725 INIT card #%d", card);
F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);
V1725_softwareReset(card);
v1725_loadConfiguration(card);
V1725_boardID(card);
v1725_saveConfiguration(card);
//


