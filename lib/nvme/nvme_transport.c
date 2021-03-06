/*-
 *   BSD LICENSE
 *
 *   Copyright (c) Intel Corporation.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * NVMe transport abstraction
 */

#include "nvme_internal.h"

#ifdef DEBUG
static __attribute__((noreturn)) void
nvme_transport_unknown(enum spdk_nvme_transport transport)
{
	SPDK_ERRLOG("Unknown transport %d\n", (int)transport);
	abort();
}
#define TRANSPORT_DEFAULT(transport)	default: nvme_transport_unknown(transport);
#else
#define TRANSPORT_DEFAULT(transport)
#endif

#define TRANSPORT_PCIE(func_name, args)	case SPDK_NVME_TRANSPORT_PCIE: return nvme_pcie_ ## func_name args;

#define NVME_TRANSPORT_CALL(transport, func_name, args) 	\
	do {							\
		switch (transport) {				\
		TRANSPORT_PCIE(func_name, args)			\
		TRANSPORT_DEFAULT(transport)			\
		}						\
		SPDK_UNREACHABLE();				\
	} while (0)


struct spdk_nvme_ctrlr *nvme_transport_ctrlr_construct(enum spdk_nvme_transport transport,
		void *devhandle)
{
	NVME_TRANSPORT_CALL(transport, ctrlr_construct, (transport, devhandle));
}

int
nvme_transport_ctrlr_destruct(struct spdk_nvme_ctrlr *ctrlr)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_destruct, (ctrlr));
}

int
nvme_transport_ctrlr_enable(struct spdk_nvme_ctrlr *ctrlr)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_enable, (ctrlr));
}

int
nvme_transport_ctrlr_get_pci_id(struct spdk_nvme_ctrlr *ctrlr, struct spdk_pci_id *pci_id)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_get_pci_id, (ctrlr, pci_id));
}

int
nvme_transport_ctrlr_set_reg_4(struct spdk_nvme_ctrlr *ctrlr, uint32_t offset, uint32_t value)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_set_reg_4, (ctrlr, offset, value));
}

int
nvme_transport_ctrlr_set_reg_8(struct spdk_nvme_ctrlr *ctrlr, uint32_t offset, uint64_t value)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_set_reg_8, (ctrlr, offset, value));
}

int
nvme_transport_ctrlr_get_reg_4(struct spdk_nvme_ctrlr *ctrlr, uint32_t offset, uint32_t *value)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_get_reg_4, (ctrlr, offset, value));
}

int
nvme_transport_ctrlr_get_reg_8(struct spdk_nvme_ctrlr *ctrlr, uint32_t offset, uint64_t *value)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_get_reg_8, (ctrlr, offset, value));
}

uint32_t
nvme_transport_ctrlr_get_max_xfer_size(struct spdk_nvme_ctrlr *ctrlr)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_get_max_xfer_size, (ctrlr));
}

struct spdk_nvme_qpair *
nvme_transport_ctrlr_create_io_qpair(struct spdk_nvme_ctrlr *ctrlr, uint16_t qid,
				     enum spdk_nvme_qprio qprio)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_create_io_qpair, (ctrlr, qid, qprio));
}

int
nvme_transport_ctrlr_delete_io_qpair(struct spdk_nvme_ctrlr *ctrlr, struct spdk_nvme_qpair *qpair)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_delete_io_qpair, (ctrlr, qpair));
}

int
nvme_transport_ctrlr_reinit_io_qpair(struct spdk_nvme_ctrlr *ctrlr, struct spdk_nvme_qpair *qpair)
{
	NVME_TRANSPORT_CALL(ctrlr->transport, ctrlr_reinit_io_qpair, (ctrlr, qpair));
}

int
nvme_transport_qpair_construct(struct spdk_nvme_qpair *qpair)
{
	NVME_TRANSPORT_CALL(qpair->transport, qpair_construct, (qpair));
}

int
nvme_transport_qpair_destroy(struct spdk_nvme_qpair *qpair)
{
	NVME_TRANSPORT_CALL(qpair->transport, qpair_destroy, (qpair));
}

int
nvme_transport_qpair_enable(struct spdk_nvme_qpair *qpair)
{
	NVME_TRANSPORT_CALL(qpair->transport, qpair_enable, (qpair));
}

int
nvme_transport_qpair_disable(struct spdk_nvme_qpair *qpair)
{
	NVME_TRANSPORT_CALL(qpair->transport, qpair_disable, (qpair));
}

int
nvme_transport_qpair_reset(struct spdk_nvme_qpair *qpair)
{
	NVME_TRANSPORT_CALL(qpair->transport, qpair_reset, (qpair));
}

int
nvme_transport_qpair_fail(struct spdk_nvme_qpair *qpair)
{
	NVME_TRANSPORT_CALL(qpair->transport, qpair_fail, (qpair));
}

int
nvme_transport_qpair_submit_request(struct spdk_nvme_qpair *qpair, struct nvme_request *req)
{
	NVME_TRANSPORT_CALL(qpair->transport, qpair_submit_request, (qpair, req));
}

int32_t
nvme_transport_qpair_process_completions(struct spdk_nvme_qpair *qpair, uint32_t max_completions)
{
	NVME_TRANSPORT_CALL(qpair->transport, qpair_process_completions, (qpair, max_completions));
}
