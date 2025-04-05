#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>

#ifndef DMTHUOC_HPP
#define DMTHUOC_HPP

using namespace std;

// DMThuoc: với các thông tin như mã thuốc, tên thuốc, đơn vị tính, giá bán, công dụng.
class DMThuoc
{
protected:
    string maThuoc;
    string tenThuoc;
    string donViTinh;
    int giaBan;
    string congDung;
    bool f; // Cờ đánh dấu trạng thái xóa (true: đã xóa, false: chưa xóa)

public:
    // Hàm tạo mặc định
    DMThuoc() : maThuoc(""), tenThuoc(""), donViTinh(""), giaBan(0), congDung(""), f(false) {}

    // Setter
    void setMaThuoc(string& ma) { maThuoc = ma; }
    void setTenThuoc(string& ten) { tenThuoc = ten; }
    void setDonViTinh(string& donVi) { donViTinh = donVi; }
    void setGiaBan(int gia) { giaBan = gia; }
    void setCongDung(string& congDung) { this->congDung = congDung; }
    void setF(bool trangThai) { f = trangThai; }

    // Getter
    string getMaThuoc() { return maThuoc; }
    string getTenThuoc() { return tenThuoc; }
    string getDonViTinh() { return donViTinh; }
    int getGiaBan() { return giaBan; }
    string getCongDung() { return congDung; }
    bool getF() { return f; }

    // Hàm đọc dữ liệu từ file
    static void docFile(vector<DMThuoc>& ds) {
        ifstream file("DMThuoc.txt", ios::in);
        if (!file.is_open()) {
            std::cout << "Khong the mo file de doc" << std::endl;
            return;
        }
    
        DMThuoc thuoc;
        string fStr;
        while (getline(file, thuoc.maThuoc)) {
            getline(file, thuoc.tenThuoc);
            getline(file, thuoc.donViTinh);
            file >> thuoc.giaBan;
            file.ignore();
            getline(file, thuoc.congDung);
            getline(file, fStr);
            thuoc.f = (fStr == "1"); // Chuyển từ string sang bool
            ds.push_back(thuoc);
        }
        file.close();
    }

    // Ghi toàn bộ danh sách vào file
    static void ghiFile(const vector<DMThuoc>& danhSachThuoc) {
        ofstream file("DMThuoc.txt", ios::trunc); // Ghi đè file
        if (!file.is_open()) {
            cout << "Khong the mo file de ghi!" << endl;
            return;
        }

        for (const auto& thuoc : danhSachThuoc) {
            file << thuoc.maThuoc << "\n";
            file << thuoc.tenThuoc << "\n";
            file << thuoc.donViTinh << "\n";
            file << thuoc.giaBan << "\n";
            file << thuoc.congDung << "\n";
            file << (thuoc.f ? "1" : "0") << "\n";
        }
        file.close();
    }

    // Hàm in danh sách thuốc dưới dạng bảng (chỉ hiển thị các thuốc chưa bị xóa)
    static void inDanhSachThuoc(const vector<DMThuoc>& ds) {
        // Kiểm tra xem danh sách có dữ liệu chưa bị xóa không
        bool coDuLieu = false;
        for (const auto& thuoc : ds) {
            if (!thuoc.f) {
                coDuLieu = true;
                break;
            }
        }
        if (!coDuLieu) {
            cout << "Danh sach thuoc rong!" << endl;
            return;
        }

        // Độ rộng cột
        const int w1 = 10;  
        const int w2 = 45; 
        const int w3 = 15;  
        const int w4 = 9;  
        const int w5 = 70;  

        // In dòng trên cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;

        // In tiêu đề cột
        cout << "|" << left << setw(w1) << "Ma Thuoc"
             << "|" << setw(w2) << "Ten Thuoc"
             << "|" << setw(w3) << "Don Vi Tinh"
             << "|" << setw(w4) << "Gia Ban"
             << "|" << setw(w5) << "Cong Dung" << "|" << endl;

        // In đường phân cách giữa tiêu đề và dữ liệu
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;

        // In dữ liệu (chỉ in các thuốc chưa bị xóa)
        for (size_t i = 0; i < ds.size(); i++) {
            if (!ds[i].f) {
                cout << "|" << right << setw(w1) << ds[i].maThuoc
                     << "|" << left << setw(w2) << ds[i].tenThuoc
                     << "|" << setw(w3) << ds[i].donViTinh
                     << "|" << right << setw(w4) << ds[i].giaBan
                     << "|" << left << setw(w5) << ds[i].congDung << "|" << endl;

                // In đường phân cách giữa các dòng (trừ dòng cuối)
                bool coDongTiepTheo = false;
                for (size_t j = i + 1; j < ds.size(); j++) {
                    if (!ds[j].f) {
                        coDongTiepTheo = true;
                        break;
                    }
                }
                if (coDongTiepTheo) {
                    cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
                         << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;
                }
            }
        }

        // In dòng dưới cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;
    }

    // Hàm kiểm tra mã thuốc có trùng hay không
    static bool kiemTraMaTrung(vector<DMThuoc>& danhSachThuoc, const string& ma) {
        for (auto& thuoc : danhSachThuoc) {
            if (thuoc.getMaThuoc() == ma) {
                return true; // Mã đã tồn tại
            }
        }
        return false; // Mã không trùng
    }

    // Hàm lấy phần số từ mã thuốc (giả sử mã có định dạng Txxx)
    static int layPhanSo(const string& ma) {
        if (ma.length() < 2 || ma.substr(0, 1) != "T") {
            return 0; // Mã không đúng định dạng
        }
        string soStr = ma.substr(1); // Lấy phần số (sau "T")
        try {
            return stoi(soStr);
        } catch (...) {
            return 0; // Nếu không chuyển đổi được, trả về 0
        }
    }

    // Hàm tạo mã mới (tăng phần số lên 1)
    static string taoMaMoi(vector<DMThuoc>& danhSachThuoc) {
        int maxSo = 0;
        for (auto& thuoc : danhSachThuoc) {
            int so = layPhanSo(thuoc.getMaThuoc());
            if (so > maxSo) {
                maxSo = so;
            }
        }
        maxSo++; // Tăng lên 1 để tạo mã mới
        // Định dạng mã mới: Txxx (ví dụ: T001, T025)
        char maMoi[10];
        sprintf(maMoi, "T%03d", maxSo); // Định dạng số với 3 chữ số (001, 025, ...)
        return string(maMoi);
    }

    // Hàm thêm thuốc (tự động tạo mã nếu trùng)
    static void themThuoc(vector<DMThuoc>& danhSachThuoc) {
        DMThuoc thuoc;
        string ma;

        // Nhập mã thuốc
        cout << "Nhap ma thuoc (dinh dang Txxx, vi du T001): ";
        getline(cin, ma);

        // Kiểm tra mã có trùng không
        if (kiemTraMaTrung(danhSachThuoc, ma)) {
            cout << "Ma thuoc da ton tai! Tu dong tao ma moi...\n";
            ma = taoMaMoi(danhSachThuoc);
            cout << "Ma moi duoc tao: " << ma << "\n";
        }

        // Gán mã và nhập các thông tin còn lại
        thuoc.setMaThuoc(ma);
        string tenThuoc, donViTinh, congDung;
        int giaBan;
        cout << "Nhap ten thuoc: "; getline(cin, tenThuoc);
        cout << "Nhap don vi tinh: "; getline(cin, donViTinh);
        cout << "Nhap gia ban: "; cin >> giaBan;
        cin.ignore();
        cout << "Nhap cong dung: "; getline(cin, congDung);
        thuoc.setTenThuoc(tenThuoc);
        thuoc.setDonViTinh(donViTinh);
        thuoc.setGiaBan(giaBan);
        thuoc.setCongDung(congDung);

        // Thêm vào danh sách
        danhSachThuoc.push_back(thuoc);

        // Ghi lại vào file
        ofstream file("DMThuoc.txt", ios::app); // Mở file ở chế độ append
        if (file.is_open()) {
            file << thuoc.getMaThuoc() << "\n";
            file << thuoc.getTenThuoc() << "\n";
            file << thuoc.getDonViTinh() << "\n";
            file << thuoc.getGiaBan() << "\n";
            file << thuoc.getCongDung() << "\n";
            file << (thuoc.f ? "1" : "0") << "\n";
            file.close();
            cout << "Them thuoc thanh cong!\n";
        } else {
            cout << "Khong the mo file de ghi!\n";
        }
    }

    // Hàm sửa thông tin thuốc
    static void suaThuoc(vector<DMThuoc>& danhSachThuoc) {
        string ma;
        cout << "Nhap ma thuoc can sua: ";
        getline(cin, ma);

        bool found = false;
        for (auto& thuoc : danhSachThuoc) {
            if (thuoc.getMaThuoc() == ma && !thuoc.f) {
                found = true;
                cout << "Tim thay thuoc: " << thuoc.getTenThuoc() << "\n";
                cout << "Nhap thong tin moi (nhan Enter de giu nguyen):\n";

                string input;
                int giaBan;
                cout << "Ten thuoc (" << thuoc.getTenThuoc() << "): ";
                getline(cin, input);
                if (!input.empty()) thuoc.setTenThuoc(input);

                cout << "Don vi tinh (" << thuoc.getDonViTinh() << "): ";
                getline(cin, input);
                if (!input.empty()) thuoc.setDonViTinh(input);

                cout << "Gia ban (" << thuoc.getGiaBan() << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    giaBan = stoi(input);
                    thuoc.setGiaBan(giaBan);
                }

                cout << "Cong dung (" << thuoc.getCongDung() << "): ";
                getline(cin, input);
                if (!input.empty()) thuoc.setCongDung(input);

                // Ghi lại toàn bộ danh sách vào file
                ghiFile(danhSachThuoc);
                cout << "Sua thong tin thuoc thanh cong!\n";
                break;
            }
        }

        if (!found) {
            cout << "Khong tim thay thuoc voi ma " << ma << " hoac thuoc da bi xoa!\n";
        }
    }

    // Hàm xóa thuốc (sử dụng cờ f)
    static void xoaThuoc(vector<DMThuoc>& danhSachThuoc) {
        string ma;
        cout << "Nhap ma thuoc can xoa: ";
        getline(cin, ma);

        bool found = false;
        for (auto& thuoc : danhSachThuoc) {
            if (thuoc.getMaThuoc() == ma && !thuoc.f) {
                found = true;
                thuoc.setF(true);
                cout << "Da danh dau xoa thuoc: " << thuoc.getTenThuoc() << "\n";

                // Ghi lại toàn bộ danh sách vào file
                ghiFile(danhSachThuoc);
                cout << "Xoa thuoc thanh cong!\n";
                break;
            }
        }

        if (!found) {
            cout << "Khong tim thay thuoc voi ma " << ma << " hoac thuoc da bi xoa!\n";
        }
    }

    // Hàm tạo menu quản lý danh mục thuốc
    static void menuQuanLyThuoc(vector<DMThuoc>& danhSachThuoc) {
        int luaChon;
        do {
            cout << "\n--- QUAN LY DANH MUC THUOC ---\n";
            cout << "1. Them thuoc\n";
            cout << "2. Sua thong tin thuoc\n";
            cout << "3. Xoa thuoc\n";
            cout << "4. Hien thi danh sach thuoc\n";
            cout << "5. Quay lai\n";
            cout << "Nhap lua chon: ";
            cin >> luaChon;
            cin.ignore(); // Xóa bộ đệm sau khi nhập số

            switch (luaChon) {
                case 1:
                    cout << "=== THEM THUOC ===\n";
                    themThuoc(danhSachThuoc);
                    break;
                case 2:
                    cout << "=== SUA THONG TIN THUOC ===\n";
                    suaThuoc(danhSachThuoc);
                    break;
                case 3:
                    cout << "=== XOA THUOC ===\n";
                    xoaThuoc(danhSachThuoc);
                    break;
                case 4:
                    cout << "=== DANH SACH THUOC ===\n";
                    inDanhSachThuoc(danhSachThuoc);
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