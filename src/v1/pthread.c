static void * process_pthread(void *arg)
{
  int s;
  while(1)
    {
      s=pthread_mutex_lock(&p_lock);
      int fd;
      if(s!=0)
	printf("##mutex_lock error\n");
      read(p_to_p[0],&fd,4);
      s=pthread_mutex_unlock(&p_lock);
      int status;
      status=process(fd);
      if(status==5)
	{
	  /*s=pthread_mutex_lock(&clean_lock);
	  if(s!=0)
	    printf("##mutex_clean error\n");
	  write(fd_clean[1],&fd,4);
	  s=pthread_mutex_unlock(&clean_lock);*/
	  close(fd);
	  //printf("######FD#######||%d||###closed###\n",fd);
	}
    }
}


int init_pthread(int num)
{
  int i;
  int s;
  for(i=0;i<num;i++)
    {
      pthread_t t;
      s=pthread_create(&t,NULL,process_pthread,NULL);
      if(s!=0)
	printf("||||create pthread error :pid:%d\n",i);
    }
  return 0;
}


