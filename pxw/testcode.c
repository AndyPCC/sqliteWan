#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <pthread.h>
#define _DEBUG_
/* pxw
 *   综合测试
 *   insert
 *   select
 *   delete
 */




void *worker(void *arg) 
{

	sqlite3 *db = NULL;
	char *zErrMsg = 0;
	int rc;

    printf("enter worker id = %d.\n", *(int*)arg);
    //sqlite3_initialize();
    //sleep(*(int*)arg * 3);
	//open
	rc = sqlite3_open("test_all.db", &db);
	if(rc) {
		fprintf(stderr, "cannot open database: %s.\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);

	} else {
		fprintf(stdout, "successfully open test_all.db.\n");
	}

	printf("------------------------- BEGIN TRANSACTION --------------------------\n");

	//事务开始	
	sqlite3_exec( db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

	//insert
	
/*	
	fprintf(stdout, "create table.\n");
	char *sql = "CREATE TABLE user( \
				 id INTEGER PRIMARY KEY, \
				 name VARCHAR(12), \
				 password VARCHAR(12), \
				 gender INTEGER);";
	sqlite3_exec( db, sql, 0, 0, &zErrMsg);

	#ifdef _DEBUG_
	printf("insert zErrMsg = %s\n", zErrMsg);
	#endif
	
	printf("----------------------------------------------------------------------\n");
	
	char *sql1 = "INSERT INTO user VALUES(1, 'zhangsan', '123', 1);";
	sqlite3_exec(db, sql1, 0, 0,&zErrMsg);
	printf("----------------------------------------------------------------------\n");
   	char *sql2 = "INSERT INTO user VALUES(2, 'lisi', '456', 1);";
  	sqlite3_exec(db, sql2, 0 , 0, &zErrMsg);
	printf("----------------------------------------------------------------------\n");
   	char *sql3 = "INSERT INTO user VALUES(3, 'wangwu', '789', 1);";
  	sqlite3_exec(db, sql3, 0 , 0, &zErrMsg);
    
	
  
	sqlite3_exec( db, "COMMIT TRANSACTION;", NULL, NULL, NULL);
 */
   	char *sql4 = "INSERT INTO user VALUES(4, 'aaaaaa', '444', 1);";
  	sqlite3_exec(db, sql4, 0 , 0, &zErrMsg);	
	printf("------------------------- COMMIT --------------------------\n");
	sqlite3_exec( db, "COMMIT TRANSACTION;", NULL, NULL, NULL);


	printf("------------------------- BEGIN TRANSACTION --------------------------\n");
	sqlite3_exec( db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	char *sql5 = "INSERT INTO user VALUES(5, 'bbbbbb', '555', 1);";
  	sqlite3_exec(db, sql5, 0 , 0, &zErrMsg);

	printf("------------------------- ROLLBACK --------------------------\n");
	sqlite3_exec( db, "ROLLBACK TRANSACTION;", NULL, NULL, NULL);
	
	

   //select
	int nrow = 0, ncolumn = 0;  
	char **azResult; //二维数组存放结果  
/*	
	//查询数据  
	
	int sqlite3_get_table(sqlite3*, const char *sql,char***result , int *nrow , int *ncolumn ,char **errmsg ); 
	result中是以数组的形式存放你所查询的数据，首先是表名，再是数据。 
	nrow ,ncolumn分别为查询语句返回的结果集的行数，列数，没有查到结果时返回0 
     */  
/*
     char *sql = "SELECT * FROM user ";  
	 sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );  
	 int i = 0 ;  
     printf( "row:%d column=%d\n" , nrow , ncolumn );  
	 printf( "\nThe result of querying is :\n" );             
	 
	 for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )  
	 printf( "Result[%d] = %s\n", i , azResult[i] );  
	 //释放掉  azResult 的内存空间  
	 sqlite3_free_table( azResult );     
	 #ifdef _DEBUG_  
	 printf("zErrMsg = %s\n", zErrMsg);  
	 #endif  
	sqlite3_exec( db, "COMMIT TRANSACTION;", NULL, NULL, NULL);

	
    sleep(*(int*)arg * 3);
*/    
	sqlite3_close(db);
	 return 0;

}

int main(void) 
{

	int i = 0;
	pthread_t tid1, tid2;
	int id[2] = {1,2};
	pthread_create(&tid1, NULL, worker, &id[0]);
//	pthread_create(&tid2, NULL, worker, &id[1]);
	pthread_join(tid1,NULL);
//	pthread_join(tid2,NULL);

	return 0;
}
