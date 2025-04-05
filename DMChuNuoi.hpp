#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>

#ifndef DMCHUNUOI_HPP
#define DMCHUNUOI_HPP

using namespace std;

// DMChuNuoi: với các thông tin như mã chủ nuôi, tên chủ nuôi, địa chỉ, số điện thoại, thông tin thú cưng.
class DMChuNuoi {
protected:
    string maChuNuoi;
    string tenChuNuoi;
    string diaChi;
    string soDienThoai;
    string thongTinThuCung;
    bool f; // Cờ đánh dấu trạng thái xóa (true: đã xóa, false: chưa xóa)

public:
    // Hàm tạo mặc định
    DMChuNuoi() : maChuNuoi(""), tenChuNuoi(""), diaChi(""), soDienThoai(""), thongTinThuCung(""), f(false) {}

    // Phương thức setter
    void setMaChuNuoi(string& ma) { maChuNuoi = ma; }
    void setTenChuNuoi(string& ten) { tenChuNuoi = ten; }
    void setDiaChi(string& dia) { diaChi = dia; }
    void setSoDienThoai(string& sdt) { soDienThoai = sdt; }
    void setThongTinThuCung(string& thuCung) { thongTinThuCung = thuCung; }
    void setF(bool trangThai) { f = trangThai; }

    // Getter
    string getMaChuNuoi() { return maChuNuoi; }
    string getTenChuNuoi() { return tenChuNuoi; }
    string getDiaChi() { return diaChi; }
    string getSoDienThoai() { return soDienThoai; }
    string getThongTinThuCung() { return thongTinThuCung; }
    bool getF() { return f; }

    // Đọc dữ liệu từ file vào vector
    static void docFile(vector<DMChuNuoi>& ds) {
        ifstream file("DMChuNuoi.txt");
        if (!file.is_open()) {
            cout << "Không thể mở file để đọc" << endl;
            return;
        }
    
        DMChuNuoi cn;
        string fStr;
        while (getline(file, cn.maChuNuoi)) {
            getline(file, cn.tenChuNuoi);
            getline(file, cn.diaChi);
            getline(file, cn.soDienThoai);
            getline(file, cn.thongTinThuCung);
            getline(file, fStr);
            cn.f = (fStr == "1"); // Chuyển từ string sang bool
            ds.push_back(cn);
        }
        file.close();
    }

    // Ghi toàn bộ danh sách vào file
    static void ghiFile(const vector<DMChuNuoi>& danhSachChuNuoi) {
        ofstream file("DMChuNuoi.txt", ios::trunc); // Ghi đè file
        if (!file.is_open()) {
            cout << "Không thể mở file để ghi!" << endl;
            return;
        }

        for (const auto& cn : danhSachChuNuoi) {
            file << cn.maChuNuoi << "\n";
            file << cn.tenChuNuoi << "\n";
            file << cn.diaChi << "\n";
            file << cn.soDienThoai << "\n";
            file << cn.thongTinThuCung << "\n";
            file << (cn.f ? "1" : "0") << "\n";
        }
        file.close();
    }

    // Hàm hiển thị danh sách chủ nuôi (chỉ hiển thị các chủ nuôi chưa bị xóa)
    static void inDanhSachChuNuoi(vector<DMChuNuoi>& danhSachChuNuoi) {
        int w1 = 10, w2 = 25, w3 = 30, w4 = 15, w5 = 70;
    
        
        // Kiểm tra xem danh sách có rỗng không
        bool coDuLieu = false;
        for (const auto& cn : danhSachChuNuoi) {
            if (!cn.f) {
                coDuLieu = true;
                break;
            }
        }
        if (!coDuLieu) {
            cout << "Danh sach chu nuoi rong!" << endl;
            return;
        }

        // In dòng trên cùng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" 
             << string(w5, '-') << "+" << endl;
    
        // In tiêu đề
        cout << "|" << left << setw(w1) << "MaKH" 
             << "|" << setw(w2) << "TenChuNuoi" 
             << "|" << setw(w3) << "ThongTinThuCung" 
             << "|" << setw(w4) << "SoDienThoai" 
             << "|" << setw(w5) << "DiaChi" << "|" << endl;
    
        // In đường phân cách
        cout << "+" << string(w1,'-') <<"+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" 
             << string(w5, '-') << "+" << endl;
    
        // In dữ liệu (chỉ in các chủ nuôi chưa bị xóa)
        for (size_t i = 0; i < danhSachChuNuoi.size(); i++) {
            if (!danhSachChuNuoi[i].f) {
                cout << "|" << right << setw(w1) << danhSachChuNuoi[i].maChuNuoi 
                     << "|" << left << setw(w2) << danhSachChuNuoi[i].tenChuNuoi 
                     << "|" << setw(w3) << danhSachChuNuoi[i].thongTinThuCung 
                     << "|" << right << setw(w4) << danhSachChuNuoi[i].soDienThoai 
                     << "|" << left << setw(w5) << danhSachChuNuoi[i].diaChi << "|" << endl;

                // In đường phân cách giữa các dòng (trừ dòng cuối)
                bool coDongTiepTheo = false;
                for (size_t j = i + 1; j < danhSachChuNuoi.size(); j++) {
                    if (!danhSachChuNuoi[j].f) {
                        coDongTiepTheo = true;
                        break;
                    }
                }
                if (coDongTiepTheo) {
                    cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
                         << string(w3, '-') << "+" << string(w4, '-') << "+" 
                         << string(w5, '-') << "+" << endl;
                }
            }
        }
    
        // In dòng dưới cùng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" 
             << string(w5, '-') << "+" << endl;
    }

    // Hàm kiểm tra mã chủ nuôi có trùng hay không
    static bool kiemTraMaTrung(vector<DMChuNuoi>& danhSachChuNuoi, const string& ma) {
        for (auto& cn : danhSachChuNuoi) {
            if (cn.getMaChuNuoi() == ma) {
                return true; // Mã đã tồn tại
            }
        }
        return false; // Mã không trùng
    }

    // Hàm lấy phần số từ mã chủ nuôi (giả sử mã có định dạng CNxxx)
    static int layPhanSo(const string& ma) {
        if (ma.length() < 3 || ma.substr(0, 2) != "CN") {
            return 0; // Mã không đúng định dạng
        }
        string soStr = ma.substr(2); // Lấy phần số (sau "CN")
        try {
            return stoi(soStr);
        } catch (...) {
            return 0; // Nếu không chuyển đổi được, trả về 0
        }
    }

    // Hàm tạo mã mới (tăng phần số lên 1)
    static string taoMaMoi(vector<DMChuNuoi>& danhSachChuNuoi) {
        int maxSo = 0;
        for (auto& cn : danhSachChuNuoi) {
            int so = layPhanSo(cn.getMaChuNuoi());
            if (so > maxSo) {
                maxSo = so;
            }
        }
        maxSo++; // Tăng lên 1 để tạo mã mới
        // Định dạng mã mới: CNxxx (ví dụ: CN001, CN025)
        char maMoi[10];
        sprintf(maMoi, "CN%03d", maxSo); // Định dạng số với 3 chữ số (001, 025, ...)
        return string(maMoi);
    }

    // Hàm thêm chủ nuôi (Phương án 2: Tự động tạo mã nếu trùng)
    static void themChuNuoi(vector<DMChuNuoi>& danhSachChuNuoi) {
        DMChuNuoi cn;
        string ma;

        // Nhập mã chủ nuôi
        cout << "Nhập mã chủ nuôi (định dạng CNxxx, ví dụ CN001): ";
        getline(cin, ma);

        // Kiểm tra mã có trùng không
        if (kiemTraMaTrung(danhSachChuNuoi, ma)) {
            cout << "Mã chủ nuôi đã tồn tại! Tự động tạo mã mới...\n";
            ma = taoMaMoi(danhSachChuNuoi);
            cout << "Mã mới được tạo: " << ma << "\n";
        }

        // Gán mã và nhập các thông tin còn lại
        cn.setMaChuNuoi(ma);
        string tenChuNuoi, diaChi, soDienThoai, thongTinThuCung;
        cout << "Nhập tên chủ nuôi: "; getline(cin, tenChuNuoi);
        cout << "Nhập địa chỉ: "; getline(cin, diaChi);
        cout << "Nhập số điện thoại: "; getline(cin, soDienThoai);
        cout << "Nhập thông tin thú cưng: "; getline(cin, thongTinThuCung);
        cn.setTenChuNuoi(tenChuNuoi);
        cn.setDiaChi(diaChi);
        cn.setSoDienThoai(soDienThoai);
        cn.setThongTinThuCung(thongTinThuCung);

        // Thêm vào danh sách
        danhSachChuNuoi.push_back(cn);

        // Ghi lại vào file
        ofstream file("DMChuNuoi.txt", ios::app); // Mở file ở chế độ append
        if (file.is_open()) {
            file << cn.getMaChuNuoi() << "\n";
            file << cn.getTenChuNuoi() << "\n";
            file << cn.getDiaChi() << "\n";
            file << cn.getSoDienThoai() << "\n";
            file << cn.getThongTinThuCung() << "\n";
            file << (cn.f ? "1" : "0") << "\n";
            file.close();
            cout << "Thêm chủ nuôi thành công!\n";
        } else {
            cout << "Không thể mở file để ghi!\n";
        }
    }

    // Hàm sửa thông tin chủ nuôi
    static void suaChuNuoi(vector<DMChuNuoi>& danhSachChuNuoi) {
        string ma;
        cout << "Nhập mã chủ nuôi cần sửa: ";
        getline(cin, ma);

        bool found = false;
        for (auto& cn : danhSachChuNuoi) {
            if (cn.getMaChuNuoi() == ma && !cn.f) {
                found = true;
                cout << "Tìm thấy chủ nuôi: " << cn.getTenChuNuoi() << "\n";
                cout << "Nhập thông tin mới (nhấn Enter để giữ nguyên):\n";

                string input;
                cout << "Tên chủ nuôi (" << cn.getTenChuNuoi() << "): ";
                getline(cin, input);
                if (!input.empty()) cn.setTenChuNuoi(input);

                cout << "Địa chỉ (" << cn.getDiaChi() << "): ";
                getline(cin, input);
                if (!input.empty()) cn.setDiaChi(input);

                cout << "Số điện thoại (" << cn.getSoDienThoai() << "): ";
                getline(cin, input);
                if (!input.empty()) cn.setSoDienThoai(input);

                cout << "Thông tin thú cưng (" << cn.getThongTinThuCung() << "): ";
                getline(cin, input);
                if (!input.empty()) cn.setThongTinThuCung(input);

                // Ghi lại toàn bộ danh sách vào file
                ghiFile(danhSachChuNuoi);
                cout << "Sửa thông tin chủ nuôi thành công!\n";
                break;
            }
        }

        if (!found) {
            cout << "Không tìm thấy chủ nuôi với mã " << ma << " hoặc chủ nuôi đã bị xóa!\n";
        }
    }

    // Hàm xóa chủ nuôi (sử dụng cờ f)
    static void xoaChuNuoi(vector<DMChuNuoi>& danhSachChuNuoi) {
        string ma;
        cout << "Nhập mã chủ nuôi cần xóa: ";
        getline(cin, ma);

        bool found = false;
        for (auto& cn : danhSachChuNuoi) {
            if (cn.getMaChuNuoi() == ma && !cn.f) {
                found = true;
                cn.setF(true);
                cout << "Đã đánh dấu xóa chủ nuôi: " << cn.getTenChuNuoi() << "\n";

                // Ghi lại toàn bộ danh sách vào file
                ghiFile(danhSachChuNuoi);
                cout << "Xóa chủ nuôi thành công!\n";
                break;
            }
        }

        if (!found) {
            cout << "Không tìm thấy chủ nuôi với mã " << ma << " hoặc chủ nuôi đã bị xóa!\n";
        }
    }

    // Hàm tạo menu quản lý danh sách chủ nuôi
    static void menuQuanLyChuNuoi(vector<DMChuNuoi>& danhSachChuNuoi) {
        int luaChon;
        do {
            cout << "\n--- QUAN LY DANH SACH CHU NUOI ---\n";
            cout << "1. Them chu nuoi\n";
            cout << "2. Sua thong tin chu nuoi\n";
            cout << "3. Xoa chu nuoi\n";
            cout << "4. Hien thi danh sach chu nuoi\n";
            cout << "5. Quay lai\n";
            cout << "Nhap lua chon: ";
            cin >> luaChon;
            cin.ignore(); // Xóa bộ đệm sau khi nhập số

            switch (luaChon) {
                case 1:
                    cout << "=== THEM CHU NUOI ===\n";
                    themChuNuoi(danhSachChuNuoi);
                    break;
                case 2:
                    cout << "=== SUA THONG TIN CHU NUOI ===\n";
                    suaChuNuoi(danhSachChuNuoi);
                    break;
                case 3:
                    cout << "=== XOA CHU NUOI ===\n";
                    xoaChuNuoi(danhSachChuNuoi);
                    break;
                case 4:
                    cout << "=== DANH SACH CHU NUOI ===\n";
                    inDanhSachChuNuoi(danhSachChuNuoi);
                    break;
                case 5:
                    cout << "Quay lai menu chinh.\n";
                    return;
                default:
                    cout << "Lua chon khong hop le! Vui long nhap lai.\n";
                    continue;
            }

            cout << "Nhan Enter de tiep tuc...";
            cin.get();
        } while (luaChon != 5);
    }
};

#endif