#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>
#include "DMThuoc.hpp"
#include "DMChuNuoi.hpp"
#include "PhieuKhamBenh.hpp"
#include "PhieuKhamBenh.cpp"
#include "LichTiemPhong.hpp"

#include <thread>
#include <chrono>

using namespace std;

// Hàm xóa màn hình (tùy hệ điều hành)
void clearScreen() {
    system("cls"); // Windows
}

// Hàm tạo hiệu ứng gõ chữ
void typingEffect(const string& text, int delay = 50) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

// Hàm hiển thị banner tiêu đề hệ thống
void hienThiBanner() {
    cout << R"(
   █████████  ██████    ██████   ████████   ████████  ████████
  ██░░░░░░░░  ██░░░██   ██░░░░██  ░░░██░░░  ██░░░░██  ██░░░░██
 ░██          ███████░  ██░   ██    ░██     ██    ██ ░██    ██    ░██
 ░████████░   ██░░░░██░ ████████    ░██     ██   ░██  ██   ░██
 ░██░░░░░░░   ██   ░██░ ██░░░░██    ░██     ██   ░██  ██   ░██
 ░██      ░   ██   ░██░ ██   ░██    ░██     ██   ░██  ██   ░██
 ░████████░   ██   ░██░ ██   ░██    ░██     ███████  ░███████
  ░░░░░░░░    ░░    ░░  ░░    ░░     ░░     ░░░░░░░   ░░░░░░░

)";
}

// Hàm hiển thị menu hệ thống

   
void hienThiMenu() {
cout<<   "-------------------------------------------------------------\n";
cout<<   "|         🏥 HỆ THỐNG QUẢN LÝ PHÒNG KHÁM THÚ Y 🐶🐱         |\n";
cout<<   "-------------------------------------------------------------\n";
    cout << "===================================================\n";
    cout << "|  [1]  📂 Quản lý danh sách chủ nuôi             |\n";
    cout << "|  [2]  💊 Quản lý danh mục thuốc                 |\n";
    cout << "|  [3]  📜 Quản lý danh sách phiếu khám bệnh      |\n";
    cout << "|  [4]  💰 Thống kê doanh thu                     |\n";
    cout << "|  [5]  📈 Thống kê thuốc sử dụng nhiều nhất      |\n";
    cout << "|  [6]  📤 Xuất báo cáo khám bệnh ra file         |\n";
    cout << "|  [7]  🗓️  Lịch nhắc tiêm phòng                   |\n";
    cout << "|  [0]  🚪 Thoát chương trình                     |\n";
    cout << "==================================================\n";
    
}


// Hàm hiển thị khung viền động khi mở chương trình
void hieuUngVien() {
    string border = "----------------------------------------------";
    for (int i = 0; i <= border.length(); i++) {
        cout << "\r" << border.substr(0, i) << flush;
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    cout << endl;
}






// Hàm chính
int main() {
    

    int luaChon;
    hieuUngVien();   // Hiệu ứng viền mở đầu
        hienThiBanner(); // Hiển thị banner hệ thống
        hienThiMenu();   // Hiển thị menu chức năng // Hiển thị giao diện người dùng
        
        vector <PhieuKhamBenh> danhSachPhieu;
        // Đọc file vào vector
        PhieuKhamBenh::docFile(danhSachPhieu);

        vector<DMThuoc> danhSachThuoc;
        DMThuoc::docFile(danhSachThuoc);

        vector<DMChuNuoi> danhSachChuNuoi;
        DMChuNuoi::docFile(danhSachChuNuoi);

        vector<LichTiemPhong> danhSachLichTiem;
        LichTiemPhong::docFile(danhSachLichTiem);
        
        // Khai báo vector doanh thu
        vector<DoanhThu> doanhThuNgay, doanhThuThang, doanhThuNam;


    do {
        cout << "Nhap lua chon: ";
       std::cin>>luaChon;
        
        switch (luaChon) {
            case 1:
                // Quản lý danh sách chủ nuôi
                DMChuNuoi::menuQuanLyChuNuoi(danhSachChuNuoi);
                break;
            case 2:
                // Quản lý danh mục thuốc
                DMThuoc::menuQuanLyThuoc(danhSachThuoc);
                break;
            case 3:
                // Quản lý danh sách phiếu khám bệnh
                PhieuKhamBenh::menuQuanLyPhieuKhamBenh(danhSachPhieu, danhSachChuNuoi, danhSachThuoc);
                break;
            case 4:
                // Thống kê doanh thu
                menuThongKeDoanhThu(danhSachPhieu, danhSachThuoc);
                break;
            case 5:
                // Thống kê thuốc sử dụng nhiều nhất
                thongKeLoaiThuoc(danhSachPhieu, danhSachThuoc);
                break;
            case 6:
                // Xuất báo cáo khám bệnh ra file
                PhieuKhamBenh::xuatBaoCaoKhamBenhRaFile(danhSachPhieu, "BaoCaoKhamBenh.txt");
                break;
            case 7:
                // Lịch nhắc tiêm phòng
                LichTiemPhong::menuQuanLyLichTiemPhong(danhSachLichTiem, danhSachChuNuoi);
                break;
            
            case 0:
                cout << "Thoát chương trình.\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ! Vui lòng thử lại.\n";
                continue;
            
        }
        cout << "Nhấn enter để tiếp tục...\n";
       cin.get();
    } while (luaChon != 0);

    


return 0;

}