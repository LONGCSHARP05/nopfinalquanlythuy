#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "PhieuKhamBenh.hpp"
#include "DMChuNuoi.hpp"
#include "DMThuoc.hpp"

using namespace std;

struct DoanhThu {  //tạo struct doanh thu để lưu doanh thu, có thuộc tính ngày và tongTien
    string ngay;
    int tongTien;
};

int layGiaThuoc(vector<DMThuoc>& danhSachThuoc, const string& maThuoc) {
    for (auto& thuoc : danhSachThuoc) {
        if (thuoc.getMaThuoc() == maThuoc) {
            return thuoc.getGiaBan();
        }
    }
    return 0;
}

// Tìm vị trí của ngày/tháng/năm trong vector 
int timViTri(vector<DoanhThu>& ds,  string& ngay) {
    for (int i = 0; i < ds.size(); i++) {
        if (ds[i].ngay == ngay) {
            return i;
        }
    }
    return -1;
}

// Tính doanh thu theo ngày, tháng, năm
void tinhDoanhThu(vector<PhieuKhamBenh>& danhSachPhieu, vector<DMThuoc>& danhSachThuoc,
                   vector<DoanhThu>& doanhThuNgay, vector<DoanhThu>& doanhThuThang, vector<DoanhThu>& doanhThuNam) {
    for (auto& pk : danhSachPhieu) {
        int giaThuoc = layGiaThuoc(danhSachThuoc, pk.getMaThuoc());
        int thanhTien = giaThuoc * pk.getSoLuongThuoc();

        string ngay = pk.getNgayKham();
        string thangNam = ngay.substr(0, 7); // "YYYY-MM"
        string nam = ngay.substr(0, 4); // "YYYY"

        // Cộng dồn doanh thu theo ngày
        int viTriNgay = timViTri(doanhThuNgay, ngay);
        if (viTriNgay != -1) {
            doanhThuNgay[viTriNgay].tongTien += thanhTien;
        } else {
            doanhThuNgay.push_back({ngay, thanhTien});
        }

        // Cộng dồn doanh thu theo tháng
        int viTriThang = timViTri(doanhThuThang, thangNam);
        if (viTriThang != -1) {
            doanhThuThang[viTriThang].tongTien += thanhTien;
        } else {
            doanhThuThang.push_back({thangNam, thanhTien});
        }

        // Cộng dồn doanh thu theo năm
        int viTriNam = timViTri(doanhThuNam, nam);
        if (viTriNam != -1) {
            doanhThuNam[viTriNam].tongTien += thanhTien;
        } else {
            doanhThuNam.push_back({nam, thanhTien});
        }
    }
}

void sapXepDoanhThu(vector<DoanhThu>& doanhThuNgay, vector<DoanhThu>& doanhThuThang, vector<DoanhThu>& doanhThuNam) {
    // Sắp xếp doanh thu theo ngày/tháng/năm
    sort(doanhThuNgay.begin(), doanhThuNgay.end(), [](const DoanhThu& a, const DoanhThu& b) {
        return a.ngay > b.ngay;
    });
    sort(doanhThuThang.begin(), doanhThuThang.end(), [](const DoanhThu& a, const DoanhThu& b) {
        return a.ngay > b.ngay;
    });
    sort(doanhThuNam.begin(), doanhThuNam.end(), [](const DoanhThu& a, const DoanhThu& b) {
        return a.ngay > b.ngay;
    });
}

// Hàm in thống kê doanh thu dưới dạng bảng
static void inThongKeDoanhThu( vector<DoanhThu>& ds,  string loai) {
    // Lọc các mục có doanh thu > 0
    vector<DoanhThu> dsLoc;
    for ( auto& dt : ds) {
        if (dt.tongTien > 0) {
            dsLoc.push_back(dt);
        }
    }

    if (dsLoc.empty()) {
        cout << "Khong co du lieu doanh thu " << loai << "!" << endl;
        return;
    }

    // Độ rộng cột
     int w1 = 15; // ThoiGian (Ngày/Tháng/Năm)
     int w2 = 25; // TongDoanhThu (đủ để chứa số lớn và "VND")

    // In dòng trên cùng của bảng
    cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" << endl;

    // In tiêu đề cột
    string tieuDe;
    if (loai == "NGAY") {
        tieuDe = "Ngay";
    } else if (loai == "THANG") {
        tieuDe = "Thang";
    } else if (loai == "NAM") {
        tieuDe = "Nam";
    }
    cout << "|" << left << setw(w1) << tieuDe
         << "|" << setw(w2) << "Tong Doanh Thu" << "|" << endl;

    // In đường phân cách giữa tiêu đề và dữ liệu
    cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" << endl;

    // In dữ liệu
    for (int i = 0; i < dsLoc.size(); i++) {
        // Tạo chuỗi đầy đủ: số + " VND"
        string doanhThuStr = to_string(dsLoc[i].tongTien) + " VND";
        // Cắt ngắn chuỗi nếu vượt quá độ dài cột
        if (doanhThuStr.length() > w2) {
            doanhThuStr = doanhThuStr.substr(0, w2 - 3) + "...";
        }
        cout << "|" << left << setw(w1) << dsLoc[i].ngay
             << "|" << setw(w2) << doanhThuStr << "|" << endl;

        // In đường phân cách giữa các dòng dữ liệu (trừ dòng cuối)
        if (i < dsLoc.size() - 1) {
            cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" << endl;
        }
    }

    // In dòng dưới cùng của bảng
    cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" << endl;
}

// Hàm menu thống kê doanh thu
static void menuThongKeDoanhThu(vector<PhieuKhamBenh>& dsPhieu, vector<DMThuoc>& dsThuoc) {
    vector<DoanhThu> doanhThuNgay, doanhThuThang, doanhThuNam;

    // Tính doanh thu trước
    tinhDoanhThu(dsPhieu, dsThuoc, doanhThuNgay, doanhThuThang, doanhThuNam);

    int luaChon;
    do {
        cout << "\n--- THONG KE DOANH THU ---\n";
        cout << "1. Doanh thu theo NGAY\n";
        cout << "2. Doanh thu theo THANG\n";
        cout << "3. Doanh thu theo NAM\n";
        cout << "4. Quay lai\n";
        cout << "Nhap lua chon: ";
        cin >> luaChon;
        cin.ignore(); // Thêm để xử lý ký tự newline sau khi nhập số

        switch (luaChon) {
            case 1:
                cout << "=== DOANH THU THEO NGAY ===\n";
                inThongKeDoanhThu(doanhThuNgay, "NGAY");
                break;
            case 2:
                cout << "=== DOANH THU THEO THANG ===\n";
                inThongKeDoanhThu(doanhThuThang, "THANG");
                break;
            case 3:
                cout << "=== DOANH THU THEO NAM ===\n";
                inThongKeDoanhThu(doanhThuNam, "NAM");
                break;
            case 4:
                cout << "Quay lai menu chinh.\n";
                return;
            default:
                cout << "Lua chon khong hop le! Vui long nhap lai.\n";
                continue;
        }

        cout << "Nhan Enter de tiep tuc...";
        cin.get();
    } while (luaChon != 4);
}


/*4. Thống kê loại thuốc sử dụng nhiều nhất*/

// duyệt tất cả những phiếu khám unique trong danh sách phiếu khám vào 1 vector khác(trước đó đã vector đọc dữ liệu phiếu khám từ file PhieuKhamBenh.txt)
// nếu phiếu khám đã tồn tại trong vector thì cộng dồn số lượng thuốc vào số lượng thuốc đã có
// sau đó sắp xếp vector theo số lượng thuốc giảm dần
// tìm max của số lượng thuốc và in ra mã thuốc, tên thuốc và số lượng thuốc của thuốc đó
// Struct lưu thông tin thống kê loại thuốc


// Struct lưu thông tin thống kê loại thuốc
struct ThongKeThuoc {
    string maThuoc;
    string tenThuoc;
    int soLuong;
};

// Hàm tìm tên thuốc từ danh sách DMThuoc
string timTenThuoc( vector<DMThuoc>& danhSachThuoc,  string& maThuoc) {
    for ( auto& thuoc : danhSachThuoc) {
        if (thuoc.getMaThuoc() == maThuoc) {
            return thuoc.getTenThuoc();
        }
    }
    return "Không tìm thấy";
}

// Hàm thống kê loại thuốc sử dụng nhiều nhất (chỉ in 3 trường: Mã Thuốc, Tên Thuốc, Số Lượng)
void thongKeLoaiThuoc(vector<PhieuKhamBenh>& danhSachPhieu, vector<DMThuoc>& danhSachThuoc) {
    // Vector lưu thông tin thống kê
    vector<ThongKeThuoc> dsThongKe;

    // Bước 1: Nhóm các phiếu khám theo mã thuốc
    for ( auto& pk : danhSachPhieu) {
        string maThuoc = pk.getMaThuoc();
        int soLuong = pk.getSoLuongThuoc();

        // Tìm xem đã có mục nào với mã thuốc này chưa
        bool found = false;
        for (auto& tk : dsThongKe) {
            if (tk.maThuoc == maThuoc) {
                tk.soLuong += soLuong;
                found = true;
                break;
            }
        }

        // Nếu chưa có, thêm mới vào danh sách
        if (!found) {
            string tenThuoc = timTenThuoc(danhSachThuoc, maThuoc);
            dsThongKe.push_back({maThuoc, tenThuoc, soLuong});
        }
    }

    // Bước 2: Sắp xếp theo số lượng giảm dần
    for (size_t i = 0; i < dsThongKe.size(); i++) {
        for (size_t j = i + 1; j < dsThongKe.size(); j++) {
            if (dsThongKe[i].soLuong < dsThongKe[j].soLuong) {
                ThongKeThuoc temp = dsThongKe[i];
                dsThongKe[i] = dsThongKe[j];
                dsThongKe[j] = temp;
            }
        }
    }

    // Bước 3: In thống kê
    cout << "=== THỐNG KÊ LOẠI THUỐC SỬ DỤNG NHIỀU NHẤT ===\n";

    if (dsThongKe.empty()) {
        cout << "Không có dữ liệu để thống kê.\n";
        return;
    }

    // Lấy số lượng lớn nhất (top 1)
    int maxSoLuong = dsThongKe[0].soLuong;

    // Độ rộng cột
     int w1 = 10;  
     int w2 = 50;
     int w3 = 10;  
    // In dòng trên cùng của bảng
    cout << string(w1 + w2 + w3 + 4, '-') << "\n";

    // In tiêu đề cột
    cout << "| " << left << setw(w1) << "Ma Thuoc"
         << "| " << setw(w2) << "Ten Thuoc"
         << "| " << setw(w3) << "So Luong" << "|\n";

    // In đường phân cách giữa tiêu đề và dữ liệu
    cout << string(w1 + w2 + w3 + 4, '-') << "\n";

    // In dữ liệu (chỉ in các mục có số lượng bằng top 1)
    int tongSoLuong = 0;
    for ( auto& tk : dsThongKe) {
        if (tk.soLuong == maxSoLuong) {
            cout << "| " << right << setw(w1) << tk.maThuoc
                 << "| " << left << setw(w2) << tk.tenThuoc
                 << "| " << right << setw(w3) << tk.soLuong << "|\n";
        }
    }

    // In đường phân cách trước dòng tổng
    cout << string(w1 + w2 + w3 + 4, '-') << "\n";


}











