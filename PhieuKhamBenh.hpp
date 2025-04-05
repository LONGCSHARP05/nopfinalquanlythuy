#ifndef PHIEUKHAMBENH_H
#define PHIEUKHAMBENH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class PhieuKhamBenh : public DMChuNuoi, public DMThuoc
{
private:
    string soPhieu;
    string ngayKham;
    string maChuNuoi;  // Chỉ lưu mã chủ nuôi, không kế thừa toàn bộ lớp DMChuNuoi
    string maThuoc;    // Chỉ lưu mã thuốc, không kế thừa toàn bộ lớp DMThuoc
    int soLuongThuoc;
    string trieuChung;
    string chanDoan;
    bool f; // Cờ đánh dấu trạng thái xóa (true: đã xóa, false: chưa xóa)

public:
    // Hàm tạo mặc định
    PhieuKhamBenh() : soPhieu(""), ngayKham(""), maChuNuoi(""), maThuoc(""), soLuongThuoc(0), trieuChung(""), chanDoan(""), f(false) {}

    // Setter
    void setSoLuongThuoc(int soLuong) { soLuongThuoc = soLuong; }
    void setMaThuoc(string ma) { maThuoc = ma; }
    void setSoPhieu(string so) { soPhieu = so; }
    void setNgayKham(string ngay) { ngayKham = ngay; }
    void setMaChuNuoi(string ma) { maChuNuoi = ma; }
    void setTrieuChung(string trieuChung) { this->trieuChung = trieuChung; }
    void setChanDoan(string chanDoan) { this->chanDoan = chanDoan; }
    void setF(bool trangThai) { f = trangThai; }

    // Getter
    string getNgayKham() const { return ngayKham; }
    string getMaThuoc() { return maThuoc; }
    string getTenThuoc() { return tenThuoc; }
    int getSoLuongThuoc() { return soLuongThuoc; }
    string getSoPhieu() { return soPhieu; }
    string getMaChuNuoi() { return maChuNuoi; }
    string getTrieuChung() { return trieuChung; }
    string getChanDoan() { return chanDoan; }
    bool getF() { return f; }

    // Hàm đọc dữ liệu từ file
    static void docFile(vector<PhieuKhamBenh>& ds) {
        ifstream file("PhieuKhamBenh.txt", ios::in);
        if (!file.is_open()) {
            cout << "Khong the mo file de doc" << endl;
            return;
        }

        PhieuKhamBenh pkb;
        string fStr;
        while (getline(file, pkb.soPhieu)) {
            getline(file, pkb.ngayKham);
            getline(file, pkb.maChuNuoi);
            getline(file, pkb.maThuoc);
            file >> pkb.soLuongThuoc;
            file.ignore();
            getline(file, pkb.trieuChung);
            getline(file, pkb.chanDoan);
            getline(file, fStr);
            pkb.f = (fStr == "1"); // Chuyển từ string sang bool
            ds.push_back(pkb);
        }
        file.close();
    }

    // Ghi toàn bộ danh sách vào file
    static void ghiFile(const vector<PhieuKhamBenh>& danhSachPhieu) {
        ofstream file("PhieuKhamBenh.txt", ios::trunc); // Ghi đè file
        if (!file.is_open()) {
            cout << "Khong the mo file de ghi!" << endl;
            return;
        }

        for (const auto& pkb : danhSachPhieu) {
            file << pkb.soPhieu << "\n";
            file << pkb.ngayKham << "\n";
            file << pkb.maChuNuoi << "\n";
            file << pkb.maThuoc << "\n";
            file << pkb.soLuongThuoc << "\n";
            file << pkb.trieuChung << "\n";
            file << pkb.chanDoan << "\n";
            file << (pkb.f ? "1" : "0") << "\n";
        }
        file.close();
    }

    // Hàm kiểm tra mã phiếu có trùng hay không
    static bool kiemTraMaTrung(vector<PhieuKhamBenh>& danhSachPhieu, const string& ma) {
        for (auto& pkb : danhSachPhieu) {
            if (pkb.getSoPhieu() == ma) {
                return true; // Mã đã tồn tại
            }
        }
        return false; // Mã không trùng
    }

    // Hàm lấy phần số từ mã phiếu (giả sử mã có định dạng PKBxxx)
    static int layPhanSo(const string& ma) {
        if (ma.length() < 4 || ma.substr(0, 3) != "PKB") {
            return 0; // Mã không đúng định dạng
        }
        string soStr = ma.substr(3); // Lấy phần số (sau "PKB")
        try {
            return stoi(soStr);
        } catch (...) {
            return 0; // Nếu không chuyển đổi được, trả về 0
        }
    }

    // Hàm tạo mã mới (tăng phần số lên 1)
    static string taoMaMoi(vector<PhieuKhamBenh>& danhSachPhieu) {
        int maxSo = 0;
        for (auto& pkb : danhSachPhieu) {
            int so = layPhanSo(pkb.getSoPhieu());
            if (so > maxSo) {
                maxSo = so;
            }
        }
        maxSo++; // Tăng lên 1 để tạo mã mới
        // Định dạng mã mới: PKBxxx (ví dụ: PKB001, PKB025)
        char maMoi[10];
        sprintf(maMoi, "PKB%03d", maxSo); // Định dạng số với 3 chữ số (001, 025, ...)
        return string(maMoi);
    }

    // Hàm thêm phiếu khám bệnh
    static void themPhieuKhamBenh(vector<PhieuKhamBenh>& danhSachPhieu, vector<DMChuNuoi>& danhSachChuNuoi, vector<DMThuoc>& danhSachThuoc) {
        PhieuKhamBenh pkb;
        string ma;

        // Nhập mã phiếu
        cout << "Nhap so phieu (dinh dang PKBxxx, vi du PKB001): ";
        getline(cin, ma);

        // Kiểm tra mã có trùng không
        if (kiemTraMaTrung(danhSachPhieu, ma)) {
            cout << "So phieu da ton tai! Tu dong tao ma moi...\n";
            ma = taoMaMoi(danhSachPhieu);
            cout << "Ma moi duoc tao: " << ma << "\n";
        }
        pkb.setSoPhieu(ma);

        // Nhập ngày khám
        cout << "Nhap ngay kham (YYYY-MM-DD): ";
        getline(cin, ma);
        pkb.setNgayKham(ma);

        // Nhập mã chủ nuôi và kiểm tra
        string maChuNuoi;
        bool chuNuoiTonTai = false;
        cout << "Nhap ma chu nuoi: ";
        getline(cin, maChuNuoi);
        for (auto& cn : danhSachChuNuoi) {
            if (cn.getMaChuNuoi() == maChuNuoi && !cn.getF()) {
                chuNuoiTonTai = true;
                break;
            }
        }
        if (!chuNuoiTonTai) {
            cout << "Ma chu nuoi khong ton tai hoac da bi xoa!\n";
            return;
        }
        pkb.setMaChuNuoi(maChuNuoi);

        // Nhập mã thuốc và kiểm tra
        string maThuoc;
        bool thuocTonTai = false;
        cout << "Nhap ma thuoc: ";
        getline(cin, maThuoc);
        for (auto& thuoc : danhSachThuoc) {
            if (thuoc.getMaThuoc() == maThuoc && !thuoc.getF()) {
                thuocTonTai = true;
                break;
            }
        }
        if (!thuocTonTai) {
            cout << "Ma thuoc khong ton tai hoac da bi xoa!\n";
            return;
        }
        pkb.setMaThuoc(maThuoc);

        // Nhập các thông tin còn lại
        int soLuongThuoc;
        string trieuChung, chanDoan;
        cout << "Nhap so luong thuoc: ";
        cin >> soLuongThuoc;
        cin.ignore();
        cout << "Nhap trieu chung: ";
        getline(cin, trieuChung);
        cout << "Nhap chan doan: ";
        getline(cin, chanDoan);
        pkb.setSoLuongThuoc(soLuongThuoc);
        pkb.setTrieuChung(trieuChung);
        pkb.setChanDoan(chanDoan);

        // Thêm vào danh sách
        danhSachPhieu.push_back(pkb);

        // Ghi lại vào file
        ofstream file("PhieuKhamBenh.txt", ios::app); // Mở file ở chế độ append
        if (file.is_open()) {
            file << pkb.getSoPhieu() << "\n";
            file << pkb.getNgayKham() << "\n";
            file << pkb.getMaChuNuoi() << "\n";
            file << pkb.getMaThuoc() << "\n";
            file << pkb.getSoLuongThuoc() << "\n";
            file << pkb.getTrieuChung() << "\n";
            file << pkb.getChanDoan() << "\n";
            file << (pkb.f ? "1" : "0") << "\n";
            file.close();
            cout << "Them phieu kham benh thanh cong!\n";
        } else {
            cout << "Khong the mo file de ghi!\n";
        }
    }

    // Hàm sửa thông tin phiếu khám bệnh (không cho phép sửa mã chủ nuôi và mã thuốc)
    static void suaPhieuKhamBenh(vector<PhieuKhamBenh>& danhSachPhieu) {
        string ma;
        cout << "Nhap so phieu can sua: ";
        getline(cin, ma);

        bool found = false;
        for (auto& pkb : danhSachPhieu) {
            if (pkb.getSoPhieu() == ma && !pkb.f) {
                found = true;
                cout << "Tim thay phieu kham benh: " << pkb.getSoPhieu() << "\n";
                cout << "Nhap thong tin moi (nhan Enter de giu nguyen):\n";

                string input;
                int soLuongThuoc;
                cout << "Ngay kham (" << pkb.getNgayKham() << "): ";
                getline(cin, input);
                if (!input.empty()) pkb.setNgayKham(input);

                cout << "So luong thuoc (" << pkb.getSoLuongThuoc() << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    soLuongThuoc = stoi(input);
                    pkb.setSoLuongThuoc(soLuongThuoc);
                }

                cout << "Trieu chung (" << pkb.getTrieuChung() << "): ";
                getline(cin, input);
                if (!input.empty()) pkb.setTrieuChung(input);

                cout << "Chan doan (" << pkb.getChanDoan() << "): ";
                getline(cin, input);
                if (!input.empty()) pkb.setChanDoan(input);

                // Ghi lại toàn bộ danh sách vào file
                ghiFile(danhSachPhieu);
                cout << "Sua thong tin phieu kham benh thanh cong!\n";
                break;
            }
        }

        if (!found) {
            cout << "Khong tim thay phieu kham benh voi so phieu " << ma << " hoac phieu da bi xoa!\n";
        }
    }

    // Hàm xóa phiếu khám bệnh (sử dụng cờ f)
    static void xoaPhieuKhamBenh(vector<PhieuKhamBenh>& danhSachPhieu) {
        string ma;
        cout << "Nhap so phieu can xoa: ";
        getline(cin, ma);

        bool found = false;
        for (auto& pkb : danhSachPhieu) {
            if (pkb.getSoPhieu() == ma && !pkb.f) {
                found = true;
                pkb.setF(true);
                cout << "Da danh dau xoa phieu kham benh: " << pkb.getSoPhieu() << "\n";

                // Ghi lại toàn bộ danh sách vào file
                ghiFile(danhSachPhieu);
                cout << "Xoa phieu kham benh thanh cong!\n";
                break;
            }
        }

        if (!found) {
            cout << "Khong tim thay phieu kham benh voi so phieu " << ma << " hoac phieu da bi xoa!\n";
        }
    }

    // Hàm so sánh để sắp xếp theo ngày khám
    static bool sosanh(PhieuKhamBenh& a, PhieuKhamBenh& b) {
        return a.ngayKham < b.ngayKham; // Sắp xếp theo ngày tăng dần
    }

    // Hàm in danh sách phiếu khám bệnh (chỉ hiển thị các phiếu chưa bị xóa)
    static void inDanhSachPhieu(vector<PhieuKhamBenh> ds) {
        // Kiểm tra xem danh sách có dữ liệu chưa bị xóa không
        bool coDuLieu = false;
        for (const auto& pkb : ds) {
            if (!pkb.f) {
                coDuLieu = true;
                break;
            }
        }
        if (!coDuLieu) {
            cout << "Danh sach phieu kham benh rong!" << endl;
            return;
        }

        // Sắp xếp theo ngày khám
        for (int i = 0; i < ds.size(); i++) {
            for (int j = i + 1; j < ds.size(); j++) {
                if (sosanh(ds[i], ds[j])) {
                    PhieuKhamBenh temp = ds[i];
                    ds[i] = ds[j];
                    ds[j] = temp;
                }
            }
        }

        // Độ rộng cột
        int w1 = 10;  
        int w2 = 15;  
        int w3 = 12;  
        int w4 = 10;  
        int w5 = 15; 
        int w6 = 25; 
        int w7 = 25;  

        // In dòng trên cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" 
             << string(w5, '-') << "+" << string(w6, '-') << "+" 
             << string(w7, '-') << "+" << endl;

        // In tiêu đề cột
        cout << "|" << left << setw(w1) << "So Phieu"
             << "|" << setw(w2) << "Ngay Kham"
             << "|" << setw(w3) << "Ma Chu Nuoi"
             << "|" << setw(w4) << "Ma Thuoc"
             << "|" << setw(w5) << "So Luong Thuoc"
             << "|" << setw(w6) << "Trieu Chung"
             << "|" << setw(w7) << "Chan Doan" << "|" << endl;

        // In đường phân cách giữa tiêu đề và dữ liệu
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" 
             << string(w5, '-') << "+" << string(w6, '-') << "+" 
             << string(w7, '-') << "+" << endl;

        // In dữ liệu (chỉ in các phiếu chưa bị xóa)
        for (size_t i = 0; i < ds.size(); i++) {
            if (!ds[i].f) {
                cout << "|" << right << setw(w1) << ds[i].soPhieu
                     << "|" << setw(w2) << ds[i].ngayKham
                     << "|" << setw(w3) << ds[i].maChuNuoi
                     << "|" << setw(w4) << ds[i].maThuoc
                     << "|" << setw(w5) << ds[i].soLuongThuoc
                     << "|" << left << setw(w6) << ds[i].trieuChung
                     << "|" << setw(w7) << ds[i].chanDoan << "|" << endl;

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
                         << string(w3, '-') << "+" << string(w4, '-') << "+" 
                         << string(w5, '-') << "+" << string(w6, '-') << "+" 
                         << string(w7, '-') << "+" << endl;
                }
            }
        }

        // In dòng dưới cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" 
             << string(w5, '-') << "+" << string(w6, '-') << "+" 
             << string(w7, '-') << "+" << endl;
    }

    // Hàm tìm kiếm và in nội dung phiếu khám bệnh (chỉ hiển thị các phiếu chưa bị xóa)
    static void inPhieuCanTim(vector<PhieuKhamBenh> ds) {
        // Nhập số phiếu cần tìm
        string soPhieuCanTim;
        cout << "\nNhap so phieu can tim: "; 
        getline(cin, soPhieuCanTim);

        vector<PhieuKhamBenh> dsTimKiem;
        // Tìm kiếm và in thông tin phiếu khám bệnh dựa trên số phiếu nhập vào
        for (int i = 0; i < ds.size(); i++) {
            if (ds[i].getSoPhieu() == soPhieuCanTim && !ds[i].f) {
                dsTimKiem.push_back(ds[i]);
            }
        }

        // Độ rộng cột
        int w1 = 10; 
        int w2 = 15;  
        int w3 = 12;  
        int w4 = 10;
        int w5 = 15; 
        int w6 = 25;  
        int w7 = 25;  


        if (dsTimKiem.empty()) {
            cout << "Khong tim thay phieu kham benh nao voi so phieu: " << soPhieuCanTim << endl;
            return;
        }

        // In dòng trên cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" 
             << string(w5, '-') << "+" << string(w6, '-') << "+" 
             << string(w7, '-') << "+" << endl;

        // In tiêu đề cột
        cout << "|" << left << setw(w1) << "So Phieu"
             << "|" << setw(w2) << "Ngay Kham"
             << "|" << setw(w3) << "Ma Chu Nuoi"
             << "|" << setw(w4) << "Ma Thuoc"
             << "|" << setw(w5) << "So Luong Thuoc"
             << "|" << setw(w6) << "Trieu Chung"
             << "|" << setw(w7) << "Chan Doan" << "|" << endl;

        // In đường phân cách giữa tiêu đề và dữ liệu
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" 
             << string(w5, '-') << "+" << string(w6, '-') << "+" 
             << string(w7, '-') << "+" << endl;

        // In dữ liệu
        for (size_t i = 0; i < dsTimKiem.size(); i++) {
            cout << "|" << right << setw(w1) << dsTimKiem[i].soPhieu
                 << "|" << setw(w2) << dsTimKiem[i].ngayKham
                 << "|" << setw(w3) << dsTimKiem[i].maChuNuoi
                 << "|" << setw(w4) << dsTimKiem[i].maThuoc
                 << "|" << setw(w5) << dsTimKiem[i].soLuongThuoc
                 << "|" << left << setw(w6) << dsTimKiem[i].trieuChung
                 << "|" << setw(w7) << dsTimKiem[i].chanDoan << "|" << endl;

            // In đường phân cách giữa các dòng (trừ dòng cuối)
            if (i < dsTimKiem.size() - 1) {
                cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
                     << string(w3, '-') << "+" << string(w4, '-') << "+" 
                     << string(w5, '-') << "+" << string(w6, '-') << "+" 
                     << string(w7, '-') << "+" << endl;
            }
        }

        // In dòng dưới cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" 
             << string(w5, '-') << "+" << string(w6, '-') << "+" 
             << string(w7, '-') << "+" << endl;
    }

    // Hàm xuất báo cáo khám bệnh ra file (chỉ xuất các phiếu chưa bị xóa)
    static void xuatBaoCaoKhamBenhRaFile(const vector<PhieuKhamBenh>& ds, string tenFile) {
        ofstream fileOut(tenFile, ios::trunc);

        if (!fileOut) {
            cerr << "Khong the mo file de ghi!\n";
            return;
        }

        // Nhập tháng báo cáo từ người dùng
        string thangBaoCao;
        cout << "Nhap thang bao cao (YYYY-MM): ";
        cin.ignore(); 
        getline(cin, thangBaoCao);

        // Header
        fileOut << "====================================\n";
        fileOut << "BAO CAO KHAM BENH THEO THANG\n";
        fileOut << "Thang bao cao: " << thangBaoCao << "\n";
        fileOut << "Dia diem: Phong Kham Thu Y ERATOO\n";
        fileOut << "====================================\n\n";

        // Lọc các phiếu khám bệnh thuộc tháng báo cáo và chưa bị xóa
        vector<PhieuKhamBenh> dsThang;
        for (const auto& phieu : ds) {
            // Lấy phần YYYY-MM từ ngày khám
            string thangKham = phieu.getNgayKham().substr(0, 7);
            if (thangKham == thangBaoCao && !phieu.f) {
                dsThang.push_back(phieu);
            }
        }

        // Nội dung
        if (dsThang.empty()) {
            fileOut << "Khong co phieu kham benh nao trong thang!\n";
        } else {
            // Sắp xếp danh sách theo ngày khám (tăng dần)
            for (int i = 0; i < dsThang.size(); i++) {
                for (int j = i + 1; j < dsThang.size(); j++) {
                    if (sosanh(dsThang[i], dsThang[j])) {
                        PhieuKhamBenh temp = dsThang[i];
                        dsThang[i] = dsThang[j];
                        dsThang[j] = temp;
                    }
                }
            }

            // Độ rộng cột
            const int w1 = 10; 
            const int w2 = 15;
            const int w3 = 12;  
            const int w4 = 10; 
            const int w5 = 15;
            const int w6 = 30;  
            const int w7 = 30;  

            // In dòng trên cùng của bảng
            fileOut << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
                    << string(w3, '-') << "+" << string(w4, '-') << "+" 
                    << string(w5, '-') << "+" << string(w6, '-') << "+" 
                    << string(w7, '-') << "+\n";

            // In tiêu đề cột
            fileOut << "|" << left << setw(w1) << "So Phieu"
                    << "|" << setw(w2) << "Ngay Kham"
                    << "|" << setw(w3) << "Ma Chu Nuoi"
                    << "|" << setw(w4) << "Ma Thuoc"
                    << "|" << setw(w5) << "So Luong Thuoc"
                    << "|" << setw(w6) << "Trieu Chung"
                    << "|" << setw(w7) << "Chan Doan" << "|\n";

            // In đường phân cách giữa tiêu đề và dữ liệu
            fileOut << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
                    << string(w3, '-') << "+" << string(w4, '-') << "+" 
                    << string(w5, '-') << "+" << string(w6, '-') << "+" 
                    << string(w7, '-') << "+\n";

            // In dữ liệu
            for (size_t i = 0; i < dsThang.size(); i++) {
                fileOut << "|" << right << setw(w1) << dsThang[i].soPhieu
                        << "|" << setw(w2) << dsThang[i].ngayKham
                        << "|" << setw(w3) << dsThang[i].maChuNuoi
                        << "|" << setw(w4) << dsThang[i].maThuoc
                        << "|" << setw(w5) << dsThang[i].soLuongThuoc
                        << "|" << left << setw(w6) << dsThang[i].trieuChung
                        << "|" << setw(w7) << dsThang[i].chanDoan << "|\n";

                if (i < dsThang.size() - 1) {
                    fileOut << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
                            << string(w3, '-') << "+" << string(w4, '-') << "+" 
                            << string(w5, '-') << "+" << string(w6, '-') << "+" 
                            << string(w7, '-') << "+\n";
                }
            }

            // In dòng dưới cùng của bảng
            fileOut << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
                    << string(w3, '-') << "+" << string(w4, '-') << "+" 
                    << string(w5, '-') << "+" << string(w6, '-') << "+" 
                    << string(w7, '-') << "+\n";
        }

        // Footer
        fileOut << "\n====================================\n";
        fileOut << "Nguoi duyet bao cao: \n";
        fileOut << "Ky xac nhan: \n";
        fileOut << "====================================\n";

        fileOut.close();
        cout << "Xuat bao cao thanh cong vao file: " << tenFile << endl;
    }

    // Hàm tạo menu quản lý phiếu khám bệnh
    static void menuQuanLyPhieuKhamBenh(vector<PhieuKhamBenh>& danhSachPhieu, vector<DMChuNuoi>& danhSachChuNuoi, vector<DMThuoc>& danhSachThuoc) {
        int luaChon;
        do {
            cout << "\n--- QUAN LY PHIEU KHAM BENH ---\n";
            cout << "1. Them phieu kham benh\n";
            cout << "2. Sua thong tin phieu kham benh\n";
            cout << "3. Xoa phieu kham benh\n";
            cout << "4. Hien thi danh sach phieu kham benh\n";
            cout << "5. Tim kiem phieu kham benh\n";
            cout << "6. Quay lai\n";
            cout << "Nhap lua chon: ";
            cin >> luaChon;
            cin.ignore(); // Xóa bộ đệm sau khi nhập số

            switch (luaChon) {
                case 1:
                    cout << "=== THEM PHIEU KHAM BENH ===\n";
                    themPhieuKhamBenh(danhSachPhieu, danhSachChuNuoi, danhSachThuoc);
                    break;
                case 2:
                    cout << "=== SUA THONG TIN PHIEU KHAM BENH ===\n";
                    suaPhieuKhamBenh(danhSachPhieu);
                    break;
                case 3:
                    cout << "=== XOA PHIEU KHAM BENH ===\n";
                    xoaPhieuKhamBenh(danhSachPhieu);
                    break;
                case 4:
                    cout << "=== DANH SACH PHIEU KHAM BENH ===\n";
                    inDanhSachPhieu(danhSachPhieu);
                    break;
                case 5:
                    cout << "=== TIM KIEM PHIEU KHAM BENH ===\n";
                    inPhieuCanTim(danhSachPhieu);
                    break;
                case 6:
                    cout << "Quay lai menu chinh.\n";
                    return;
                default:
                    cout << "Lua chon khong hop le! Vui long nhap lai.\n";
                    continue;
            }

            cout << "Nhan Enter de tiep tuc...";
            cin.get();
        } while (luaChon != 6);
    }
};

#endif