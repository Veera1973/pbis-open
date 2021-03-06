/* Editor Settings: expandtabs and use 4 spaces for indentation
 * ex: set softtabstop=4 tabstop=8 expandtab shiftwidth=4: *
 *  * -*- mode: c, c-basic-offset: 4 -*- */

/*
 * Copyright © BeyondTrust Software 2004 - 2019
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * BEYONDTRUST MAKES THIS SOFTWARE AVAILABLE UNDER OTHER LICENSING TERMS AS
 * WELL. IF YOU HAVE ENTERED INTO A SEPARATE LICENSE AGREEMENT WITH
 * BEYONDTRUST, THEN YOU MAY ELECT TO USE THE SOFTWARE UNDER THE TERMS OF THAT
 * SOFTWARE LICENSE AGREEMENT INSTEAD OF THE TERMS OF THE APACHE LICENSE,
 * NOTWITHSTANDING THE ABOVE NOTICE.  IF YOU HAVE QUESTIONS, OR WISH TO REQUEST
 * A COPY OF THE ALTERNATE LICENSING TERMS OFFERED BY BEYONDTRUST, PLEASE CONTACT
 * BEYONDTRUST AT beyondtrust.com/contact
 */
 

 /*                                                               *
 *  retireves the information from the AD about the metrics       *
 *                                                                *  
 ******************************************************************/
#include "includes.h"


/*
 *
 * Print the Metric information. 
 */
static
VOID
Lwt_LsaPrintMetrics(
    PVOID pMetrics,
    DWORD dwLevel
    );



int 
get_metrics_main(
  int argc, 
  char *argv[]
  )
{
    HANDLE hLSAConnection = NULL;
    PLSA_METRIC_PACK_0 pMetrics_0 = NULL;
    PLSA_METRIC_PACK_1 pMetrics_1 = NULL;
    PTESTDATA pTestData = NULL;
    DWORD dwError = LW_ERROR_SUCCESS;


    dwError = Lwt_LsaTestSetup(argc,
                               argv,
                               &hLSAConnection,
                               &pTestData);
    BAIL(dwError);

    
    /*Start collect the groups for the level 1*/
    dwError = LsaGetMetrics(hLSAConnection, 
                            0,
                           (PVOID *) &pMetrics_0);
    BAIL(dwError);    
    if (pMetrics_0)
    {
        Lwt_LsaPrintMetrics((PVOID) pMetrics_0, 0);
    }
    
    
    dwError = LsaGetMetrics(hLSAConnection,
                            1,
                            (PVOID *)&pMetrics_1);
    BAIL(dwError);
    
    
    
    if (pMetrics_1)
    {
        Lwt_LsaPrintMetrics((PVOID) pMetrics_1, 1);
    } 
    
    
cleanup:
    if (pMetrics_0 != NULL)
    {
       LwFreeMemory(pMetrics_0); 
       pMetrics_0 = NULL;
    }

    if (pMetrics_1 != NULL)
    {
        LwFreeMemory(pMetrics_1);
        pMetrics_1 = NULL;
    }

    Lwt_LsaTestTeardown(&hLSAConnection,
                        &pTestData);
    return dwError;

error:
    goto cleanup;

}



static
VOID
Lwt_LsaPrintMetrics(
    PVOID pMetrics,
    DWORD dwLevel
 )
{
     if (dwLevel == 0)
     {
        PLSA_METRIC_PACK_0 pMetricPack = (PLSA_METRIC_PACK_0)pMetrics;
        fprintf(stdout, "Metric info (Level-0):\n");
        fprintf(stdout, "====================\n");
        fprintf(stdout, "Statistics:\n");
        fprintf(stdout, "====================\n");
        fprintf(stdout, "Failed Authenticatin count:  %llu\n", 
                                (unsigned long long)pMetricPack->failedAuthentications);
        fprintf(stdout, "Failed User Lookups by Name:  %llu\n", 
                                (unsigned long long)pMetricPack->failedUserLookupsByName);
        fprintf(stdout, "Failed User Lookups by ID:     %llu\n", 
                                (unsigned long long)pMetricPack->failedAuthentications);
        fprintf(stdout, "Failed Group Lookups by Name:  %llu\n", 
                                (unsigned long long)pMetricPack->failedGroupLookupsByName);
        fprintf(stdout, "Failed Group Lookups by ID:  %llu\n", 
                                (unsigned long long)pMetricPack->failedGroupLookupsById);
        fprintf(stdout, "Failed Open Session  :       %llu\n", 
                                (unsigned long long)pMetricPack->failedOpenSession);
        fprintf(stdout, "Failed Close Session :       %llu\n", 
                                (unsigned long long)pMetricPack->failedCloseSession);
        fprintf(stdout, "Failed Change Passwords:      %llu\n", 
                                (unsigned long long)pMetricPack->failedChangePassword);
    }
    if(dwLevel == 1)
    {
        PLSA_METRIC_PACK_1 pMetricPack = (PLSA_METRIC_PACK_1)pMetrics;
        fprintf(stdout, "\n\n\nMetric info (Level-1):\n");
        fprintf(stdout, "====================\n");
        fprintf(stdout, "Statistics:\n");
        fprintf(stdout, "====================\n");
        fprintf(stdout, "Successful Authenticatin count:  %llu\n", 
                                (unsigned long long)pMetricPack->successfulAuthentications);
        fprintf(stdout, "Failed Authenticatin count:      %llu\n", 
                                (unsigned long long)pMetricPack->failedAuthentications);
        fprintf(stdout, "root Authentication Count:       %llu\n", 
                                (unsigned long long)pMetricPack->rootUserAuthentications);
        fprintf(stdout, "Successful User lookups by Name: %llu\n", 
                                (unsigned long long)pMetricPack->successfulUserLookupsByName);
        fprintf(stdout, "Failed User Lookups by Name:     %llu\n", 
                                (unsigned long long)pMetricPack->failedUserLookupsByName);
        fprintf(stdout, "Successful User Lookups by ID:   %llu\n", 
                                (unsigned long long)pMetricPack->successfulUserLookupsById);
        fprintf(stdout, "Failed User Lookups by ID:       %llu\n", 
                                (unsigned long long)pMetricPack->failedAuthentications);
        fprintf(stdout, "Successful Group Lookup by Name: %llu\n", 
                                (unsigned long long)pMetricPack->successfulGroupLookupsByName);
        fprintf(stdout, "Failed Group Lookups by Name:    %llu\n", 
                                (unsigned long long)pMetricPack->failedGroupLookupsByName);
        fprintf(stdout, "Successful Group Lookups by ID:  %llu\n", 
                                (unsigned long long)pMetricPack->successfulGroupLookupsById);
        fprintf(stdout, "Failed Group Lookups by ID:      %llu\n", 
                                (unsigned long long)pMetricPack->failedGroupLookupsById);
        fprintf(stdout, "Successful Open Session:         %llu\n", 
                                (unsigned long long)pMetricPack->successfulOpenSession);
        fprintf(stdout, "Failed Open Session  :           %llu\n", 
                                (unsigned long long)pMetricPack->failedOpenSession);
        fprintf(stdout, "Successful Close Session :       %llu\n", 
                                (unsigned long long)pMetricPack->successfulCloseSession);
        fprintf(stdout, "Failed Close Session :           %llu\n", 
                                (unsigned long long)pMetricPack->failedCloseSession);
        fprintf(stdout, "Successful Change Passwords:     %llu\n", 
                                (unsigned long long)pMetricPack->successfulChangePassword);
        fprintf(stdout, "Failed Change Passwords:         %llu\n", 
                                (unsigned long long)pMetricPack->failedChangePassword);

    }


}
