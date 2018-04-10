#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"
#include <QScreen>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <vector>
#include <cmath>
//#include "data_types.h"
using namespace std;

/**
* This is point class, which defines point in 3D coordinate system
*/
class point3D{
   public:
    double x_coord,y_coord,z_coord; 
  public:
    point3D(double x,double y,double z){
        x_coord = x;
        y_coord = y;
        z_coord = z;
    }
};



/**
* This is edge class, which defines edge in 3D coordinate system
*/
class edge3D{
   public:
   point3D init,final;
};


/**
* This is face class, which defines face in 3D coordinate system
*/

class face{
     public:
      int vert[10];
};


/**
* This is graph class, which defines  model of 3D solid
*/
class graph3D{
  public:
  vector<point3D> pnts; //pnts[10] = new point3D(0,0,0)[10];
  int *adjacency_matrix;
  face fac[10];
  int fc[10];
  int num,numf;
  graph3D(int n,int f) : pnts(20,point3D(0,0,0)){
 
    adjacency_matrix = (int*)malloc(n*n*sizeof(int));
 
    num = n;
    numf = f;
  }  
};


/**
* This is point class, which defines point in 2D coordinate system
*/
class point2D{
    public:
      double coord_1,coord_2;
      point2D(double x,double y){
        coord_1 = x;
        coord_2 = y;
    }
};

/**
* This is edge class, which defines point in 2D coordinate system
*/
class edge2D{
   public:
   point2D init,final;
};


/**
* This is graph class, which defines projection in 2D coordinate system
*/
class graph2D{
public:
  vector<point2D> pnts; 
  int *adjacency_matrix;
  
   face fac[10];
   int fc[10];
  int num,numf; 
  graph2D(int n,int f) : pnts(20,point2D(0,0)){
    
    adjacency_matrix = (int*)malloc(n*n*sizeof(int));
    
    num = n;
    numf = f;
    
  }  
};

point3D mov(point3D p,double x,double y,double z){

  /**
   *move function translates point p to new point p_new 
   * by shift amount of x,y,z in respective coordinates.
  */
    point3D p_new(0,0,0);
    p_new.x_coord = p.x_coord + x;
    p_new.y_coord = p.y_coord +y;
    p_new.z_coord = p.z_coord +z;
    return p_new;
}




point3D rotate(point3D p,double alpha,double beta,double gamma){
  /**
   *move function changes point p to new point p_new by rotation of coordinate axes
   * by angle of rotation  of alpha,beta,gamma in respective coordinates.
  */
     double rx[3][3],ry[3][3],rz[3][3],r[3][3],r1[3][3];
      

     rx[0][0] = 1;
     rx[0][1] = 0;
     rx[0][2] = 0;
     rx[1][0] = 0;
     rx[1][1] = cos(alpha);
     rx[1][2] = -sin(alpha);
     rx[2][0] = 0;
     rx[2][1] = sin(alpha);
     rx[2][2] = cos(alpha);

     ry[0][0] = cos(beta);
     ry[0][1] = 0;
     ry[0][2] = sin(beta);
     ry[1][0] = 0;
     ry[1][1] = 1;
     ry[1][2] = 0;
     ry[2][0] = -sin(beta);
     ry[2][1] = 0;
     ry[2][2] = cos(beta);

     rz[0][0] = cos(gamma);
     rz[0][1] = -sin(gamma);
     rz[0][2] = 0;
     rz[1][0] = sin(gamma);
     rz[1][1] = cos(gamma);
     rz[1][2] = 0;
     rz[2][0] = 0;
     rz[2][1] = 0;
     rz[2][2] = 1;


   
    double sum;  
    int i,j,k;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            sum=0;
            for(k=0; k<3; k++)
            {
                sum = sum + ry[i][k] * rz[k][j];
            }
            r1[i][j] = sum;
        }
    }


    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            sum=0;
            for(k=0; k<3; k++)
            {
                sum = sum + rx[i][k] * r1[k][j];
            }
            r[i][j] = sum;
        }
    }

     point3D p_new(0,0,0);

     p_new.x_coord = r[0][0]*p.x_coord + r[0][1]*p.y_coord + r[0][2]*p.z_coord;
     p_new.y_coord = r[1][0]*p.x_coord + r[1][1]*p.y_coord + r[1][2]*p.z_coord;
     p_new.z_coord = r[2][0]*p.x_coord + r[2][1]*p.y_coord + r[2][2]*p.z_coord;

     return p_new;
     
}

graph3D rot(graph3D g1,double alpha,double beta,double gamma){
    /**
     * rotates the whole 3D object 
     * by angle of rotation  of alpha,beta,gamma in respective coordinates.
    */
    graph3D g2(g1.num,g1.numf);
    for(int i=0;i<g1.num;i++){
        g2.pnts[i] = rotate(g1.pnts[i],alpha,beta,gamma);
    }
    for(int i=0;i<g1.num;i++){
        for(int j=0;j<g1.num;j++)
    g2.adjacency_matrix[i*g1.num+j] = g1.adjacency_matrix[i*g1.num+j];
}
    for(int i=0;i<g1.numf;i++){
   g2.fc[i] = g1.fc[i];}
   for(int i=0;i<g1.numf;i++){
    for(int j = 0;j<g1.fc[i];j++)
   g2.fac[i].vert[j] = g1.fac[i].vert[j];
   }

    
    return g2;
}

/** Lets assume type0 - xy plane-t;  type1 - yz plane-f; type2 - xz plane-s;         ****/
/* front- yz;  top- xy; side - xz;
*/
point2D point_proj(point3D p,int type){
  /**
   *given a 3D point we project it onto 2D plane based on type
  */
    point2D p1(0,0);
     if(type==0)
        {p1.coord_1 = p.x_coord;
        p1.coord_2 = p.y_coord;}
     else if(type==1)
     { p1.coord_1 = p.y_coord;
        p1.coord_2 = p.z_coord;
                     }
     else
     {p1.coord_1 = p.x_coord;
        p1.coord_2 = p.z_coord;}
      return p1;
}

int check_withinregion(vector<point2D> pl,point2D px,int pl_length){
  /**
  /* Given a point and set of vertices of face , this function checks whether the point is in this face region or not
  */
    point2D ptmp(0,0);
    int tst=1;
    for(int i=0;i<pl_length;i++){
        ptmp.coord_1 += pl[i].coord_1;
        ptmp.coord_2 += pl[i].coord_2;
    }
    ptmp.coord_1 = ptmp.coord_1/pl_length;
    ptmp.coord_2 = ptmp.coord_2/pl_length;
    
    for(int i=0;i<pl_length;i++){
        int t = (i+1)%pl_length;
        double k1 = (pl[t].coord_1-pl[i].coord_1)*(ptmp.coord_2-pl[i].coord_2)-(pl[t].coord_2-pl[i].coord_2)*(ptmp.coord_1-pl[i].coord_1);
        double k2 = (pl[t].coord_1-pl[i].coord_1)*(px.coord_2-pl[i].coord_2)-(pl[t].coord_2-pl[i].coord_2)*(px.coord_1-pl[i].coord_1);
        if(k1*k2<0)
            {  tst = 0;
                break;}

    }
    return tst;    
}


int check_abovebelowplane(vector<point3D> pl,point3D px,int type){

    /**
    /* Given a plane , a point and also projection type this function returns whether the point is above or below the plane
    */

       double a1 = pl[1].x_coord - pl[0].x_coord;
       double a2 = pl[1].y_coord - pl[0].y_coord;
       double a3 = pl[1].z_coord - pl[0].z_coord;
       double b1 = pl[2].x_coord - pl[1].x_coord;
       double b2 = pl[2].y_coord - pl[1].y_coord;
       double b3 = pl[2].z_coord - pl[1].z_coord;
       
       double comp1 = (a2 * b3 - a3 * b2), comp2 = -(a1 * b3 - a3 * b1), comp3 = (a1 * b2 - a2 * b1);
       
       double cnst = comp1*pl[0].x_coord + comp2*pl[0].y_coord + comp3*pl[0].z_coord;
       
       if(type==0){  //proj on xy plane
       if(comp3==0) //plane is perpendicular to proj plane
         return 0;
       else{
         double z = (cnst- comp1*px.x_coord - comp2*px.y_coord)/comp3;
          
         if(px.z_coord-z> -0.01)
            { //cout<<" a"<<endl;
              return 0;}
         else
            return 1;}
          
        }
       
       else if(type==1){ //proj on yz plane
        if(comp1==0) //plane is perpendicular to proj plane
         return 0;
       else{
         
         double x = (cnst- comp2*px.y_coord - comp3*px.z_coord)/comp1;
        
         if(px.x_coord-x> -0.01)
            return 0;
         else
            return 1;}
       }

       else{ //proj on xz plane
        if(comp2==0) //plane is perpendicular to proj plane
         return 0;
       else{
         double y = (cnst- comp1*px.x_coord - comp3*px.z_coord)/comp2;
         
         if(px.y_coord-y> -0.01)
            return 0;
         else
            return 1;}
       }


          //returns 1 if point is below the plane
}


int* findHiddenEdges(graph3D p,int type){
  /**
     *given a 3D graph we find hidden edges of it in a orthographic projection
     * it returns adjacency matrix of hidden edges
  */
    
    int x[p.num];
    for(int i = 0; i<p.num;i++){ 
    //for each point check whether its visible or not
        int k1 = 1;
        point2D px = point_proj(p.pnts[i],type);
       for(int j=0;j<p.numf;j++){
          vector<point2D> pl; //pl[10];
         
          vector<point3D> pl3;//[10];
         
          for(int k=0;k<p.fc[j];k++)
           { pl.push_back(point_proj(p.pnts[p.fac[j].vert[k]],type));
            pl3.push_back(p.pnts[p.fac[j].vert[k]]);}
            int y;
          
           y = check_abovebelowplane(pl3,p.pnts[i],type) + check_withinregion(pl,px,p.fc[j]);
           
          if(y==2) // point is not visible
            { k1 = 0;
              
                break;}
       }
       x[i] = k1;  // 0-> invisible 1 -> visible
       
    }
    
   int* adj = (int*)malloc(p.num*p.num*sizeof(int));
    for(int i=0;i<p.num;i++){
        for(int j=0;j<p.num;j++){
            if(p.adjacency_matrix[i*p.num+j]==1){
               
    
                point3D p11((p.pnts[i].x_coord+p.pnts[j].x_coord)/2.0,(p.pnts[i].y_coord+p.pnts[j].y_coord)/2.0,(p.pnts[i].z_coord+p.pnts[j].z_coord)/2.0);
                point2D p22 = point_proj(p11,type);
                int y=0;
                for(int j1=0;j1<p.numf;j1++){
                vector<point2D> pl;
                
                vector<point3D> pl3;//[10];
                
               for(int k=0;k<p.fc[j1];k++)
                    { pl.push_back(point_proj(p.pnts[p.fac[j1].vert[k]],type));
                        pl3.push_back(p.pnts[p.fac[j1].vert[k]]);}
                         y = check_abovebelowplane(pl3,p11,type) + check_withinregion(pl,p22,p.fc[j1]);
                         if(y==2)
                          {
                            break;}}
           
            if(x[i]==0||x[j]==0)
                 {adj[i*p.num+j] = 2;
                  }
               else if(y==2)
                {adj[i*p.num+j] = 2;
                  }
               else
                adj[i*p.num+j] = 1;
            }
            else
                adj[i*p.num+j] = 0;
        }
    } 
     
    return adj;
}

graph2D orthographic_projection(graph3D p,int type,int proj_type){
  /**
     *given a 3D graph we convert it into 2D projection
     *type defines kind of view of the projection - top,front,side.
     * proj_type defines kind of projection 1st angle or third angle
  */
    graph2D g1(p.num,p.numf);

    
     for(int i=0;i<p.num;i++){
        g1.pnts[i] = point_proj(p.pnts[i],type);}

   g1.adjacency_matrix = findHiddenEdges(p,type); 
   for(int i=0;i<p.numf;i++){
   g1.fc[i] = p.fc[i];}
   for(int i=0;i<p.numf;i++){
    for(int j = 0;j<p.fc[i];j++)
   g1.fac[i].vert[j] = p.fac[i].vert[j];
   }
   return g1;
}

point3D combine_points(point2D top,point2D front,point2D side,int proj_type){
  /**
  * given a point in all three projections we generate three dimensional coordinate of it.
  * we assume top view -> xy; front -> yz; side -> xz;
  */
  point3D p(0,0,0);
  p.x_coord = top.coord_1;
  p.y_coord = top.coord_2;
  p.z_coord = front.coord_2;
  return p;
}

graph3D generate_wireframe(graph2D top,graph2D front,graph2D side,int proj_type){
    /**
    *given all three orthographic projections it returns 3d solid
    * We have all the points present in each of the three views in same order 
    * the above two functions generate edges and points respectively in 3D coordinate system
    * type denotes 1st angle or 3rd angle projection
    */
     graph3D g1(top.num,top.numf);
     for(int i=0;i<top.num;i++){
      g1.pnts[i] = combine_points(top.pnts[i],front.pnts[i],side.pnts[i],proj_type);
     }
    for(int i=0;i<top.num;i++){
      for(int j=0;j<top.num;j++){
        if(top.adjacency_matrix[i*top.num+j]==0)
        g1.adjacency_matrix[i*top.num+j] = 0;
          else
            g1.adjacency_matrix[i*top.num+j] = 1;
      }
    }

    for(int i=0;i<top.numf;i++){
   g1.fc[i] = top.fc[i];}
   for(int i=0;i<top.numf;i++){
    for(int j = 0;j<top.fc[i];j++)
   g1.fac[i].vert[j] = top.fac[i].vert[j];
   }

   
    return g1;
}






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // glwidget = new GLWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

   

   void  MainWindow::on_actionRead_triggered(){
   	filename = QFileDialog::getOpenFileName(this, tr("Open File:"), "/Users/ravijayanth/Desktop/qt-ex/copt1/");
   	 qInfo() << filename;
     QFile file(filename);
     file.open(QIODevice::ReadOnly);
     QTextStream in(&file);
     QString line = in.readLine();
     //QStringList res = line.split(" ");
       if(line.toInt()==3){
        QString lin1 = in.readLine();
        QStringList result = lin1.split(" ");
        ui->widget->n = result[0].toInt();
        int n1 = result[0].toInt();
        ui->widget->f =  result[1].toInt();
         graph3D g1(ui->widget->n,ui->widget->f);
         graph2D gt(ui->widget->n,ui->widget->f),gf(ui->widget->n,ui->widget->f),gs(ui->widget->n,ui->widget->f);
        lin1 = in.readLine();
        ui->widget->m1 = lin1.toInt();
        for(int i=0;i<ui->widget->n;i++){
           lin1 = in.readLine();
           result = lin1.split(" ");
           ui->widget->vertices[i][0] = result[0].toFloat();
           g1.pnts[i].x_coord = ui->widget->vertices[i][0];
           ui->widget->vertices[i][1] = result[1].toFloat();
           g1.pnts[i].y_coord = ui->widget->vertices[i][1];
           ui->widget->vertices[i][2] = result[2].toFloat();
           g1.pnts[i].z_coord = ui->widget->vertices[i][2];
        }

        for(int i=0;i<ui->widget->f;i++){
             lin1 = in.readLine();
             //result = lin1.split(" ");
             ui->widget->a[i] = lin1.toInt();
             g1.fc[i] = ui->widget->a[i];
              QString lin2 = in.readLine();
              result = lin2.split(" ");
          for(int j=0;j<ui->widget->a[i];j++){
               
                //QStringList result1 = lin2.split(" ");
                ui->widget->facets[i][j] = result[j].toInt();
                g1.fac[i].vert[j] = result[j].toInt();
              }
          }
          
          for(int i=0;i<ui->widget->n;i++){
           
              lin1 = in.readLine();
              result = lin1.split(" ");
               for(int j=0;j<ui->widget->n;j++){
                g1.adjacency_matrix[i*n1+j] = result[j].toInt();
            }
          }

          lin1 = in.readLine();
          result = lin1.split(" ");
          ui->widget->al = result[0].toFloat();
          ui->widget->bt = result[1].toFloat();
          ui->widget->gm = result[2].toFloat();

          g1 = rot(g1,ui->widget->al,ui->widget->bt,ui->widget->gm);

          for(int i=0;i<ui->widget->n;i++){
            ui->widget->vertices[i][0] = g1.pnts[i].x_coord;
            ui->widget->vertices[i][1] = g1.pnts[i].y_coord;
            ui->widget->vertices[i][2] = g1.pnts[i].z_coord;

          }
          gt = orthographic_projection(g1,0,0);
          gf = orthographic_projection(g1,1,0);
          gs = orthographic_projection(g1,2,0);

          for( int i=0;i<n1;i++){  // for adjacency matrix of edges
    for(int j=0;j<n1;j++){
      ui->widget->admt[i][j] = gt.adjacency_matrix[i*n1+j];
      
      ui->widget->admf[i][j] = gf.adjacency_matrix[i*n1+j];
      
      ui->widget->adms[i][j] = gs.adjacency_matrix[i*n1+j];
      
    }}
 for(int i=0;i<n1;i++){
    ui->widget->vert2t[i][0] = gt.pnts[i].coord_1;
    ui->widget->vert2t[i][1] = gt.pnts[i].coord_2;

    ui->widget->vert2f[i][0] = gf.pnts[i].coord_1;
    ui->widget->vert2f[i][1] = gf.pnts[i].coord_2;

    ui->widget->vert2s[i][0] = gs.pnts[i].coord_1;
    ui->widget->vert2s[i][1] = gs.pnts[i].coord_2;
   } 



       }

     
     if(line.toInt()==2){
        QString lin1 = in.readLine();
        QStringList result = lin1.split(" ");
        ui->widget->n = result[0].toInt();
        int n1 = result[0].toInt();
        ui->widget->f =  result[1].toInt();
        graph3D g1(ui->widget->n,ui->widget->f);
         graph2D gt(ui->widget->n,ui->widget->f),gf(ui->widget->n,ui->widget->f),gs(ui->widget->n,ui->widget->f);
       
        lin1 = in.readLine();
        ui->widget->m1 = lin1.toInt();
        
        for(int i=0;i<ui->widget->n;i++){
           lin1 = in.readLine();
           result = lin1.split(" ");
           ui->widget->vert2t[i][0] = result[0].toFloat();
           gt.pnts[i].coord_1 = result[0].toFloat();
           ui->widget->vert2t[i][1] = result[1].toFloat();
           gt.pnts[i].coord_2 = result[1].toFloat();
        }
        for(int i=0;i<ui->widget->n;i++){
           lin1 = in.readLine();
           result = lin1.split(" ");
           ui->widget->vert2f[i][0] = result[0].toFloat();
           gf.pnts[i].coord_1 = result[0].toFloat();
           ui->widget->vert2f[i][1] = result[1].toFloat();
           gf.pnts[i].coord_2 = result[1].toFloat();
        }
        for(int i=0;i<ui->widget->n;i++){
           lin1 = in.readLine();
           result = lin1.split(" ");
           ui->widget->vert2s[i][0] = result[0].toFloat();
           gs.pnts[i].coord_1 = result[0].toFloat();
           ui->widget->vert2s[i][1] = result[1].toFloat();
           gs.pnts[i].coord_1 = result[0].toFloat();
        }
         for(int i=0;i<ui->widget->f;i++){
             lin1 = in.readLine();
             //result = lin1.split(" ");
             ui->widget->a[i] = lin1.toInt();
             gf.fc[i] = lin1.toInt();
             gt.fc[i] = lin1.toInt();
             gs.fc[i] = lin1.toInt();
              QString lin2 = in.readLine();
              result = lin2.split(" ");
          for(int j=0;j<ui->widget->a[i];j++){
               
                //QStringList result1 = lin2.split(" ");
                ui->widget->facets[i][j] = result[j].toInt();
                gf.fac[i].vert[j] = result[j].toInt();
                gt.fac[i].vert[j] = result[j].toInt();
                gs.fac[i].vert[j] = result[j].toInt();
              }
          }
           for(int i=0;i<ui->widget->n;i++){
            lin1 = in.readLine();
            QStringList result1 = lin1.split(" ");
              for(int j=0;j<ui->widget->n;j++){
              //result = lin1.split(" ");
              ui->widget->admt[i][j] = result1[j].toInt();
              gt.adjacency_matrix[i*n1+j] = result1[j].toInt();
            }
          }
          for(int i=0;i<ui->widget->n;i++){
            lin1 = in.readLine();
            QStringList result1 = lin1.split(" ");
              for(int j=0;j<ui->widget->n;j++){
              //result = lin1.split(" ");
              ui->widget->admf[i][j] = result1[j].toInt();
              gf.adjacency_matrix[i*n1+j] = result1[j].toInt();
            }
          }
          for(int i=0;i<ui->widget->n;i++){
            lin1 = in.readLine();
            QStringList result1 = lin1.split(" ");
              for(int j=0;j<ui->widget->n;j++){
              //result = lin1.split(" ");
              ui->widget->adms[i][j] = result1[j].toInt();
              gs.adjacency_matrix[i*n1+j] = result1[j].toInt();
            }
          }
          g1 = generate_wireframe(gt,gf,gs,0);

          for(int i=0;i<ui->widget->n;i++){
            ui->widget->vertices[i][0] = g1.pnts[i].x_coord;
            ui->widget->vertices[i][1] = g1.pnts[i].y_coord;
            ui->widget->vertices[i][2] = g1.pnts[i].z_coord;
          }

     }
     file.close();
     
   }

   void   MainWindow::on_actionGenerate_3d_file_triggered(){
           QFileDialog fileDlg( this );
     fileDlg.setWindowTitle( "diectory to save file" );
    fileDlg.setDirectory( "/Users/ravijayanth/Desktop/qt-ex/copt1" );
    fileDlg.setFileMode( QFileDialog::DirectoryOnly );
    fileDlg.setOptions( QFileDialog::ShowDirsOnly );
    fileDlg.setAcceptMode( QFileDialog::AcceptSave );

    if ( fileDlg.exec() == QDialog::Rejected )
        return;

    QString filename = (fileDlg.selectedFiles())[0];
    qInfo() << filename;
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QTextStream strm(&file);
    QString line;
    strm<<3<<endl;
    strm<<ui->widget->n<<" "<<ui->widget->f<<endl;
    strm<<ui->widget->m1<<endl;
    for(int i=0;i<ui->widget->n;i++){
      strm<<ui->widget->vertices[i][0]<<" "<<ui->widget->vertices[i][1]<<" "<<ui->widget->vertices[i][2]<<endl;
    }
    for(int i=0;i<ui->widget->f;i++){
       strm<<ui->widget->a[i]<<endl;
      for(int j=0;j<ui->widget->a[i];j++){
           strm<<ui->widget->facets[i][j]<<" ";
      }
      strm<<endl;
    }
    
    for(int i=0;i<ui->widget->n;i++){
      for(int j=0;j<ui->widget->n;j++){
        if(ui->widget->admt[i][j]==0)
          strm<<0<<" ";
        else
          strm<<1<<" ";
      }
      strm<<endl;
    }
    strm<<0<<" "<<0<<" "<<0;

    file.close();
   }
   
   void  MainWindow::on_actionGenerate_2d_File_triggered(){
      QFileDialog fileDlg( this );
     fileDlg.setWindowTitle( "Directory to save file" );
    fileDlg.setDirectory( "/Users/ravijayanth/Desktop/qt-ex/copt1" );
    fileDlg.setFileMode( QFileDialog::DirectoryOnly );
    fileDlg.setOptions( QFileDialog::ShowDirsOnly );
    fileDlg.setAcceptMode( QFileDialog::AcceptSave );

    if ( fileDlg.exec() == QDialog::Rejected )
        return;

    QString filename = (fileDlg.selectedFiles())[0];
    qInfo() << filename;
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QTextStream strm(&file);
    QString line;
    strm<<2<<endl;
    strm<<ui->widget->n<<" "<<ui->widget->f<<endl;
    strm<<ui->widget->m1<<endl;
    for(int i=0;i<ui->widget->n;i++){
      strm<<ui->widget->vert2t[i][0]<<" "<<ui->widget->vert2t[i][1]<<endl;
    }
    for(int i=0;i<ui->widget->n;i++){
      strm<<ui->widget->vert2f[i][0]<<" "<<ui->widget->vert2f[i][1]<<endl;
    }
    for(int i=0;i<ui->widget->n;i++){
      strm<<ui->widget->vert2s[i][0]<<" "<<ui->widget->vert2s[i][1]<<endl;
    }
    for(int i=0;i<ui->widget->f;i++){
       strm<<ui->widget->a[i]<<endl;
      for(int j=0;j<ui->widget->a[i];j++){
           strm<<ui->widget->facets[i][j]<<" ";
      }
      strm<<endl;
    }
    
    for(int i=0;i<ui->widget->n;i++){
      for(int j=0;j<ui->widget->n;j++){
        strm<<ui->widget->admt[i][j]<<" ";
      }
      strm<<endl;
    }
    for(int i=0;i<ui->widget->n;i++){
      for(int j=0;j<ui->widget->n;j++){
       strm<<ui->widget->admf[i][j]<<" ";
      }
      strm<<endl;
    }
    for(int i=0;i<ui->widget->n;i++){
      for(int j=0;j<ui->widget->n;j++){
        strm<<ui->widget->adms[i][j]<<" ";
      }
      strm<<endl;
    }
   

    file.close();
   }

   void   MainWindow::on_action3D_view_triggered(){
      ui->widget->m1 = 3;
    	ui->widget->updateGL();
   	 
   }

   void   MainWindow::on_action2D_topview_triggered(){
       ui->widget->m1 = 0;
       ui->widget->updateGL();
   }

   void   MainWindow::on_action2D_frontview_triggered(){
       ui->widget->m1 = 1;
       ui->widget->updateGL();
   }

   void   MainWindow::on_action2D_sideview_triggered(){
      ui->widget->m1 = 2;
      ui->widget->updateGL();
   }

   void MainWindow::on_actionScreenShot_triggered(){
     QScreen *QSCREEN = QGuiApplication::primaryScreen();
    QPixmap qpix = QSCREEN->grabWindow(this->winId(), 0, 0, QApplication::desktop()->width(),
                      QApplication::desktop()->height());

    QFileDialog fileDlg( this );
    fileDlg.setWindowTitle( "Directory to save file" );
    fileDlg.setDirectory( "/Users/ravijayanth/Desktop/qt-ex/copt1" );
    fileDlg.setFileMode( QFileDialog::DirectoryOnly );
    fileDlg.setOptions( QFileDialog::ShowDirsOnly );
    fileDlg.setAcceptMode( QFileDialog::AcceptSave );

    if ( fileDlg.exec() == QDialog::Rejected )
        return;

    QString filename = (fileDlg.selectedFiles())[0];
    qInfo() << filename;
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    qpix.save(&file, "JPG");

   }

   void MainWindow::keyPressEvent(QKeyEvent * ev){
     if(ev->key() == Qt::Key_D)
        ui->widget->zf = ui->widget->zf * 1.25;
     if(ev->key() == Qt::Key_A)
        ui->widget->zf = ui->widget->zf * 0.8;
     if(ev->key() == Qt::Key_F)
         ui->widget->xtr = ui->widget->xtr - 0.25;
     if(ev->key() == Qt::Key_J)
         ui->widget->xtr = ui->widget->xtr + 0.25;
     if(ev->key() == Qt::Key_T)
         ui->widget->ytr = ui->widget->ytr + 0.25;
     if(ev->key() == Qt::Key_B)
         ui->widget->ytr = ui->widget->ytr - 0.25;
     if(ev->key() == Qt::Key_G)
         ui->widget->ztr = ui->widget->ztr - 0.25;
     if(ev->key() == Qt::Key_H)
         ui->widget->ztr = ui->widget->ztr + 0.25;
     ui->widget->updateGL();
   }
   

