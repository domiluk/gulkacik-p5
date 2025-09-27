int super_line(BITMAP *bmp, int fx, int fy, int tx, int ty, int stroke, int clr)
{
 int max;
 int swib;
 float x, y;
 
 if(abs(fx-tx) > abs(fy-ty))
 {
  max = abs(fx-tx);
  swib = 0;
 }
 else 
 {
  max = abs(fy-ty); 
  swib = 1;
 }
 
 if(swib == 0)
 {
  if(fx < tx)
  {  
   y = fy;
   for(x = fx;x < tx;x++)
   {
    y-=(float)(fy-ty)/max;
    //circlefill(bmp,x,y,stroke,clr);       
    line(bmp,x-stroke/2,y,x+stroke/2,y,clr);
    //rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);
    //circle(bmp,x,y,stroke,clr);
   }
  }
  else
  {
   y = fy;
   for(x = fx; x > tx;x--)
   {
    y-=(float)(fy-ty)/max;
    //circlefill(bmp,x,y,stroke,clr);      
    line(bmp,x-stroke/2,y,x+stroke/2,y,clr);
    //rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);   
    //circle(bmp,x,y,stroke,clr);
   }    
  }        
 }
 
 else //swib = 1; //pre neznalych veci swib = So What Is Bigger
 {
  if(fy < ty)
  {  
   x = fx;
   for(y = fy;y < ty;y++)
   {
    x-=(float)(fx-tx)/max;
    //circlefill(bmp,x,y,stroke,clr);       
    line(bmp,x-stroke/2,y,x+stroke/2,y,clr);
    //rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);
    //circle(bmp,x,y,stroke,clr);
   }
  }
  else
  {
   x = tx;
   for(y = ty; y < fy;y++)
   {
    x-=(float)(fx-tx)/max;
    //circlefill(bmp,x,y,stroke,clr);      
       line(bmp,x-stroke/2,y,x+stroke/2,y,clr);
    //rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);
        //circle(bmp,x,y,stroke,clr);
   }    
  }          
 }
 
 //printf("max %d\n",max);
 return 1;    
}


int missin_five(BITMAP *bmp, int fx, int fy, int tx, int ty, int clr)
{
 int max;
 int swib;
 float x, y;
 
 int miss;
 miss = 0;
 if(abs(fx-tx) > abs(fy-ty))
 {
  max = abs(fx-tx);
  swib = 0;
 }
 else 
 {
  max = abs(fy-ty); 
  swib = 1;
 }
 
 if(swib == 0)
 {
  if(fx < tx)
  {  
   y = fy;
   for(x = fx;x < tx;x++)
   {
    y-=(float)(fy-ty)/max;
    //circlefill(bmp,x,y,stroke,clr);       
    if(miss <= 5)putpixel(bmp,x,y,clr);
    miss++;
    if(miss == 10)miss = 0;
    //rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);
    //circle(bmp,x,y,stroke,clr);
   }
  }
  else
  {
   y = fy;
   for(x = fx; x > tx;x--)
   {
    y-=(float)(fy-ty)/max;
    //circlefill(bmp,x,y,stroke,clr);      
    if(miss <= 5)putpixel(bmp,x,y,clr);
    miss++;
    if(miss == 10)miss = 0;
		//rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);   
    //circle(bmp,x,y,stroke,clr);
   }    
  }        
 }
 
 else //swib = 1; //pre neznalych veci swib = So What Is Bigger
 {
  if(fy < ty)
  {  
   x = fx;
   for(y = fy;y < ty;y++)
   {
    x-=(float)(fx-tx)/max;
    //circlefill(bmp,x,y,stroke,clr);       
        if(miss <= 5)putpixel(bmp,x,y,clr);
    miss++;
    if(miss == 10)miss = 0;
    //rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);
    //circle(bmp,x,y,stroke,clr);
   }
  }
  else
  {
   x = tx;
   for(y = ty; y < fy;y++)
   {
    x-=(float)(fx-tx)/max;
    //circlefill(bmp,x,y,stroke,clr);      
           if(miss <= 5)putpixel(bmp,x,y,clr);
    miss++;
    if(miss == 10)miss = 0;
    //rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);
        //circle(bmp,x,y,stroke,clr);
   }    
  }          
 }
 
 //printf("max %d\n",max);
 return 1;    
}

int missin_five_inv(BITMAP *bmp, int fx, int fy, int tx, int ty,int clr)
{
 int max;
 int swib;
 float x, y;
 
 int miss;
 miss = 0;
 if(abs(fx-tx) > abs(fy-ty))
 {
  max = abs(fx-tx);
  swib = 0;
 }
 else 
 {
  max = abs(fy-ty); 
  swib = 1;
 }
 
 if(swib == 0)
 {
  if(fx < tx)
  {  
   y = fy;
   for(x = fx;x < tx;x++)
   {
    y-=(float)(fy-ty)/max;
    //circlefill(bmp,x,y,stroke,clr);       
    if(miss <= 5)putpixel(bmp,x,y,clr);
    else putpixel(bmp,x,y,clr ^ 0xffffff);
    miss++;
    if(miss == 10)miss = 0;
    //rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);
    //circle(bmp,x,y,stroke,clr);
   }
  }
  else
  {
   y = fy;
   for(x = fx; x > tx;x--)
   {
    y-=(float)(fy-ty)/max;
    //circlefill(bmp,x,y,stroke,clr);      
    if(miss <= 5)putpixel(bmp,x,y,clr);
       else putpixel(bmp,x,y,clr ^ 0xffffff);
		miss++;
    if(miss == 10)miss = 0;
		//rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);   
    //circle(bmp,x,y,stroke,clr);
   }    
  }        
 }
 
 else //swib = 1; //pre neznalych veci swib = So What Is Bigger
 {
  if(fy < ty)
  {  
   x = fx;
   for(y = fy;y < ty;y++)
   {
    x-=(float)(fx-tx)/max;
    //circlefill(bmp,x,y,stroke,clr);       
        if(miss <= 5)putpixel(bmp,x,y,clr);
           else putpixel(bmp,x,y,clr ^ 0xffffff);
    miss++;
    if(miss == 10)miss = 0;
    //rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);
    //circle(bmp,x,y,stroke,clr);
   }
  }
  else
  {
   x = tx;
   for(y = ty; y < fy;y++)
   {
    x-=(float)(fx-tx)/max;
    //circlefill(bmp,x,y,stroke,clr);      
           if(miss <= 5)putpixel(bmp,x,y,clr);
              else putpixel(bmp,x,y,clr ^ 0xffffff);
    miss++;
    if(miss == 10)miss = 0;
    //rectfill(bmp,x-stroke/2,y-stroke/2,x+stroke/2,y+stroke/2,clr);
        //circle(bmp,x,y,stroke,clr);
   }    
  }          
 }
 
 //printf("max %d\n",max);
 return 1;    
}
