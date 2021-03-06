//
//  main.cpp
//  relayout
//
//  Created by RainJay Tsai on 2016/10/7.
//  Copyright © 2016年 RainJay Tsai. All rights reserved.
//

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Rect { // for cells
    int x; // x, y is top left corner
    int y;
    int width;
    int height;
};

struct Table {
    int width;
    int height;
    std::vector<Rect> cells; // bounding rectangles
};

void relayout(Table &table, const std::vector<int> &cell_min_heights);
int find_min_height(Table &table, const std::vector<int> &cell_min_heights, vector<int> &layout_index);
vector<int> line_sweep( const int x, const vector<Rect> &rect );
vector<int> line_sweep_y( const int x, const vector<Rect> &rect );

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Table table;
    table.width = 30;
    table.height = 24;
    table.cells.push_back((Rect){0, 0, 10, 18});
    table.cells.push_back((Rect){10, 0, 20, 10});
    table.cells.push_back((Rect){10, 10, 10, 8});
    table.cells.push_back((Rect){20, 10, 10, 14});
    table.cells.push_back((Rect){0, 18, 20, 6});
    std::vector<int> cell_min_heights;
    cell_min_heights.push_back(20);
    cell_min_heights.push_back(13);
    cell_min_heights.push_back(15);
    cell_min_heights.push_back(16);
    cell_min_heights.push_back(5);
    relayout(table, cell_min_heights);
    
    Table table2;
    table2.width = 40;
    table2.height = 70;
    table2.cells.push_back((Rect){0, 0, 20, 30});
    table2.cells.push_back((Rect){20,0,10,20 });
    table2.cells.push_back((Rect){30,0,10,30});
    table2.cells.push_back((Rect){20,20,10,10});
    table2.cells.push_back((Rect){0,30,10,40});
    table2.cells.push_back((Rect){10,30,20,20});
    table2.cells.push_back((Rect){30,30,10,40});
    table2.cells.push_back((Rect){10,50,20,20});
    std::vector<int> min_heights;
    
    min_heights.push_back(33);
    min_heights.push_back(25);
    min_heights.push_back(20);
    min_heights.push_back(17);
    min_heights.push_back(55);
    min_heights.push_back(20);
    min_heights.push_back(34);
    min_heights.push_back(28);
    
    relayout(table2, min_heights);
    
    Table table3;
    table3.width = 20;
    table3.height = 20;
    table3.cells.push_back((Rect){0, 0,10, 10});
    table3.cells.push_back((Rect){10,0,10,10 });
    table3.cells.push_back((Rect){0,10,10,10});
    table3.cells.push_back((Rect){10,10,10,10});
    
    vector<int> min_heights3;
    min_heights3.push_back(17);
    min_heights3.push_back(5);
    min_heights3.push_back(13);
    min_heights3.push_back(4);
    
    relayout(table3, min_heights3);
    
    Table table4;
    table4.width = 20;
    table4.height = 9;
    table4.cells.push_back((Rect){0, 0, 5, 6});
    table4.cells.push_back((Rect){5, 0, 15,3 });
    table4.cells.push_back((Rect){5, 3, 10,3});
    table4.cells.push_back((Rect){15, 3, 5,3});
    table4.cells.push_back((Rect){0, 6, 10,3});
    table4.cells.push_back((Rect){10,6,10, 3});
    
    min_heights3.clear();
    min_heights3.push_back(7);
    min_heights3.push_back(10);
    min_heights3.push_back(13);
    min_heights3.push_back(7);
    min_heights3.push_back(9);
    min_heights3.push_back(2);
    
    relayout(table4, min_heights3);
    
    min_heights3.clear();
    min_heights3.push_back(9);
    min_heights3.push_back(10);
    min_heights3.push_back(13);
    min_heights3.push_back(7);
    min_heights3.push_back(9);
    min_heights3.push_back(2);
    
    //relayout(table4, min_heights3);
    
    system("pause");
    return 0;
}

int find_min_height(Table &table, const std::vector<int> &cell_min_heights, vector<int> &layout_index){
    int golbal_max = 0;
    for(int x = 0; x < table.width; x++ ){
        
        int sum = 0;
        vector<int>tmp = line_sweep(x, table.cells);
        for( int i = 0 ; i < tmp.size(); i++ ){
            sum += cell_min_heights[tmp[i]];
        }
        
        if( golbal_max < sum){
            golbal_max = sum;
            layout_index = tmp;
        }
        
    }
    return golbal_max;
    
}



void relayout(Table &table, const std::vector<int> &cell_min_heights){
    vector<int> layout_index;
    bool is_relayout[ cell_min_heights.size() ];
    memset( is_relayout, 0, cell_min_heights.size()*sizeof(bool) );
    
    const int relayout_height = find_min_height(table, cell_min_heights, layout_index);
    cout << relayout_height << endl;

    
    vector<Rect> tmp = table.cells;

    for( int i = 0 ; i < tmp.size(); i++ ){
        int reheight = 0;
        for( int j = 0; j < layout_index.size(); j++){
            if( i == layout_index[j]){
                goto endfor;
            }
            if( tmp[i].y <= tmp[layout_index[j]].y && tmp[i].y + tmp[i].height >= tmp[layout_index[j]].height + tmp[layout_index[j]].y ){
                reheight += cell_min_heights[layout_index[j]];
            }
        }
        tmp[i].height = reheight;
        endfor:
            {}
    }
    for( int i = 0; i < layout_index.size(); i++){
        tmp[layout_index[i]].height = cell_min_heights[layout_index[i]];
    }
    
 

    /*
    for( int i = 0; i < tmp.size(); i++){
        for( int j = 0 ; j < tmp.size(); j++){
            if( i == j ){
                continue;
            }
            if( tmp[i].x <= tmp[j].x && tmp[i].x +tmp[i].width >= tmp[j].x && tmp[i].y < tmp[j].y){
                tmp[j].y = tmp[i].height;
            }
        }
    }*/
    
    int newy[tmp.size()];
    memset( newy, 0, tmp.size()*sizeof(int) );
    
    for( int i = 0; i < tmp.size(); i++ ){
         int y = 0;
         for( int j = 0; j < layout_index.size(); j++ ){
              if( tmp[i].y == 0 || layout_index[j] == i ){
                  break;
              }
              if( tmp[i].y >  tmp[layout_index[j]].y  ){
                  y += cell_min_heights[layout_index[j]];
              }
         }
         newy[i] = y;
    }

    for( int i = 0; i < tmp.size(); i++ ){
         tmp[i].y = newy[i];
    }

    int count = 0;
    for( vector<Rect>::iterator it = tmp.begin(); it != tmp.end(); it++){
        Rect r = (Rect)(*it);
        cout << count << " " << r.x << "," << r.y << " " << r.height << endl;
        count++;
    }
    
    return ;
}

vector<int> line_sweep( const int x, const vector<Rect> &rect ){
    vector<int> rslt;
    
    for( int i = 0; i < rect.size(); i++ ){
        if( x >= rect[i].x + 1 && x <= rect[i].x + rect[i].width ){
            rslt.push_back(i);
        }
    }
    return rslt;
}


vector<int> line_sweep_y( const int x, const vector<Rect> &rect ){
    vector<int> rslt;
    
    for( int i = 0; i < rect.size(); i++ ){
        if( x >= rect[i].x + 1 && x <= rect[i].x + rect[i].height ){
            rslt.push_back(i);
        }
    }
    return rslt;
}
